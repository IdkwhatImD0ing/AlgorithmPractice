CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: queue.o stack.o bubble.o shell.o quick.o set.o sorting.o
	$(CC) -o sorting stack.o queue.o bubble.o shell.o quick.o set.o sorting.o -lm

sorting.o:
	$(CC) $(CFLAGS) -c sorting.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f sorting sorting.o stack.o queue.o bubble.o shell.o quick.o set.o

scan-build: clean
	scan-build make

