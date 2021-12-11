CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: tsp

tsp: graph.o stack.o path.o tsp.o
	$(CC) -o tsp graph.o stack.o path.o tsp.o -lm

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f tsp graph.o stack.o path.o tsp.o

scan-build: clean
	scan-build make
