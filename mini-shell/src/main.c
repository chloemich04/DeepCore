#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXARGS 128
#define MAXJOBS 64

// simple job table
struct job {
    pid_t pid;
    char cmd[MAXLINE];
    int running;
} jobs[MAXJOBS];

int njobs = 0;

// add a background job, return its index or -1
int add_job(pid_t pid, const char *cmd){
    
    if (njobs >= MAXJOBS) return -1;

    jobs[njobs].pid = pid;
    strncpy(jobs[njobs].cmd, cmd, sizeof jobs[njobs].cmd - 1);
    jobs[njobs].cmd[sizeof jobs[njobs].cmd - 1] = '\0';
    jobs[njobs].running = 1;
    return njobs++;
}
// remove job at index i (shorten the list because we shift the array)
void remove_job(int i) {
    if (i < 0 || i >= njobs) return;

    for (; i < njobs - 1; i++) 
        jobs[i] = jobs[i + 1];
    njobs--;
}

// reap any children that have exited; call this periodically to clean up background jobs
void update_jobs(void) {
    for (int i = 0; i < njobs; ) {
        pid_t pid = jobs[i].pid;
        int status;
        pid_t r = waitpid(pid, &status, WNOHANG);
        if (r == -1) {
            if (errno == ECHILD) 
                // no such child, must have already been reaped; remove it
                remove_job(i);
            else {
                perror("waitpid");
                i++;
            }
        }
        else if (r == 0) {
            i++; // child still running
        }
        else {
            // child is finished; remove it
            printf("[%d]+  Done   %s\n", pid, jobs[i].cmd);
            remove_job(i);
        }
    }
}

// built=in command
int do_cd(char *argv[]) {

    if (argv[1] == NULL) {
        char *home = getenv("HOME");

        if (home == NULL)
            home = "/";
        
        if (chdir(home) < 0) 
            perror("cd");
    }
    else {
        if (chdir(argv[1]) < 0)
            perror("cd");
    }
    return 1; // signal that we handled the command
}

int do_jobs(char *argv[]) {
    update_jobs(); // reap any finished children first

    for (int i = 0; i < njobs; i++) {
        printf("[%d] %s   %s\n",
            jobs[i].pid,
            jobs[i].running ? "Running" : "Done",
            jobs[i].cmd);
    }
    return 1; // command is finished
}

int do_fg(char *argv[]) {
    if (njobs == 0) {
        fprintf(stderr, "fg: no current job\n");
        return 1;
    }

    // bring the most recent job to the foreground
    int idx = njobs - 1;
    pid_t pid = jobs[idx].pid;
    int status;
    if (waitpid(pid,&status, 0) == -1)
        perror("waitpid");
    remove_job(idx);
    return 1;
}

// dispatch a built-in command; return non-zero if we did something
int handle_builtin(char * argv[]) {
    if (strcmp(argv[0], "cd") == 0)
        return do_cd(argv);

    if (strcmp(argv[0], "jobs") == 0)
        return do_jobs(argv);

    if (strcmp(argv[0], "fg") == 0)
        return do_fg(argv);
    
    if (strcmp(argv[0], "exit") == 0) {
        puts("bye bye :)");
        exit(0);
    }

    
    return 0; // not a built-in
}

/* execute a single command (no piping) */
void execute_command(char *argv[], int background)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }
    if (pid == 0) {                   /* child */
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } 
    else {                          /* parent */
        if (background) {
            if (add_job(pid, argv[0]) == -1) 
                fprintf(stderr, "job table full\n");
            printf("[%d]\n", pid);
        } 
        else {
            waitpid(pid, NULL, 0);
        }
    }
}

/* execute two commands connected by a pipe */
void execute_pipe(char *argv1[], char *argv2[])
{
    int fd[2];
    
    /* create the pipe */
    if (pipe(fd) < 0) {
        perror("pipe");
        return;
    }
    
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return;
    }
    
    if (pid1 == 0) {                  /* first child (producer) */
        close(fd[0]);                 /* close read end */
        dup2(fd[1], STDOUT_FILENO);   /* redirect stdout to write end */
        close(fd[1]);
        execvp(argv1[0], argv1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return;
    }
    
    if (pid2 == 0) {                  /* second child (consumer) */
        close(fd[1]);                 /* close write end */
        dup2(fd[0], STDIN_FILENO);    /* redirect stdin to read end */
        close(fd[0]);
        execvp(argv2[0], argv2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    
    /* parent closes both ends and waits */
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(void)
{
    char line[MAXLINE];
    char *argv[MAXARGS];
    int background;

    for (;;) {
        update_jobs(); // check for any finished background jobs

        printf("mini-shell> ");
        fflush(stdout);

        if (!fgets(line, sizeof line, stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        /* tokenize the input */
        int argc = 0;
        char *tok = strtok(line, " ");
        while (tok && argc < MAXARGS - 1) {
            argv[argc++] = tok;
            tok = strtok(NULL, " ");
        }
        argv[argc] = NULL;
        if (argc == 0)
            continue;

        /* check for background */
        if (argc > 0 && strcmp(argv[argc - 1], "&") == 0) {
            background = 1;
            argv[argc - 1] = NULL;
            argc--;
        } 
        else {
            background = 0;
        }

        // handle built-in commands before doing anything else
        if (handle_builtin(argv))
            continue;

        /* check for pipe */
        int pipe_index = -1;
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "|") == 0) {
                pipe_index = i;
                break;
            }
        }

        if (pipe_index == -1) {
            /* no pipe, execute normally */
            execute_command(argv, background);
        } else {
            /* pipe found */
            argv[pipe_index] = NULL;              /* split the array */
            char *argv1[MAXARGS];
            char *argv2[MAXARGS];
            
            /* copy first part */
            for (int i = 0; i < pipe_index; i++)
                argv1[i] = argv[i];
            argv1[pipe_index] = NULL;
            
            /* copy second part */
            int j = 0;
            for (int i = pipe_index + 1; i < argc; i++)
                argv2[j++] = argv[i];
            argv2[j] = NULL;
            
            execute_pipe(argv1, argv2);
        }
    }

    puts("bye bye :)");
    return 0;
}
