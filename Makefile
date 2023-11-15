all: M0 clean

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
M0: tests/M0/move_tests.c move.o core.o
	$(CC) $(CFLAGS) -o $@  $^

move.o: core/ALU/move.c
	gcc $(CFLAGS) -c $^

core.o: core/M0/core.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o
