CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/*.c
TEST_SRC = tests/*.c

all: test

test: $(SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) $(SRC) $(TEST_SRC) -o test

clean:
	rm -f *.o *.a test