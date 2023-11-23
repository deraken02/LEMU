all: multiply_tests add_tests compare_tests logical_tests move_tests shift_tests substract_tests clean

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g


%.o: core/ALU/%.c
	gcc $(CFLAGS) -c $^

%_tests: tests/M0/%_tests.c %.o core.o
	gcc $(CFLAGS) -o $@  $^

core.o: core/M0/core.c #core/M0/*.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o
