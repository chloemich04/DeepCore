#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARGS 128

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
    } else {                          /* parent */
        if (background) {
            printf("[%d]\n", pid);
        } else {
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
        } else {
            background = 0;
        }

        /* check for exit */
        if (strcmp(argv[0], "exit") == 0)
            break;

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
