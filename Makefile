all: logical_tests move_tests clean

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
move_tests: tests/M0/move_tests.c move.o core.o
	$(CC) $(CFLAGS) -o $@  $^

logical_tests: tests/M0/logical_tests.c logical.o move.o core.o
	$(CC) $(CFLAGS) -o $@  $^

move.o: core/ALU/move.c
	gcc $(CFLAGS) -c $^

logical.o: core/ALU/logical.c
	gcc $(CFLAGS) -c $^

core.o: core/M0/core.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o
