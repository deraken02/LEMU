all: add_tests compare_tests logical_tests move_tests shift_tests clean

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

add_tests: tests/M0/add_tests.c add.o core.o
	$(CC) $(CFLAGS) -o $@  $^

compare_tests: tests/M0/compare_tests.c compare.o core.o
	$(CC) $(CFLAGS) -o $@  $^

shift_tests: tests/M0/shift_tests.c shift.o core.o
	$(CC) $(CFLAGS) -o $@  $^

move_tests: tests/M0/move_tests.c move.o core.o
	$(CC) $(CFLAGS) -o $@  $^

logical_tests: tests/M0/logical_tests.c logical.o move.o core.o
	$(CC) $(CFLAGS) -o $@  $^

add.o: core/ALU/add.c
	gcc $(CFLAGS) -c $^

compare.o: core/ALU/compare.c
	gcc $(CFLAGS) -c $^

shift.o: core/ALU/shift.c
	gcc $(CFLAGS) -c $^

move.o: core/ALU/move.c
	gcc $(CFLAGS) -c $^

logical.o: core/ALU/logical.c
	gcc $(CFLAGS) -c $^

core.o: core/M0/core.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o
