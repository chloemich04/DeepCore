CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: shell

shell: src/main.o
	$(CC) $(FLAGS) -o shell src/main.o

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o src/main.o src/main.c

clean:
	rm -f src/*.o shell