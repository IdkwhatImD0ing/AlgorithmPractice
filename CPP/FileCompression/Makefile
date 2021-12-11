CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: encode decode entropy

encode: code.o huffman.o io.o node.o pq.o stack.o encode.o
	$(CC) -o encode code.o huffman.o io.o node.o pq.o stack.o encode.o -lm -g

decode: code.o huffman.o io.o node.o pq.o stack.o decode.o
	$(CC) -o decode code.o huffman.o io.o node.o pq.o stack.o decode.o -lm -g

entropy: code.o huffman.o io.o node.o pq.o stack.o entropy.o
	$(CC) -o entropy code.o huffman.o io.o node.o pq.o stack.o entropy.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f encode decode entropy code.o huffman.o io.o node.o pq.o stack.o entropy.o decode.o encode.o

scan-build: clean
	scan-build make
