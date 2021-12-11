CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib-test 

mathlib-test: mathlib.o mathlib-test.o
	$(CC) -o mathlib-test mathlib.o mathlib-test.o -lm

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

clean:
	rm -f mathlib-test mathlib-test.o mathlib.o

scan-build: clean
	scan-build make

