CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode error entropy

encode: hamming.o bm.o bv.o encode.o
	$(CC) -o encode hamming.o bm.o bv.o encode.o -lm

decode: hamming.o bm.o bv.o decode.o
	$(CC) -o decode hamming.o bm.o bv.o decode.o -lm

error: hamming.o bm.o bv.o error.o
	 $(CC) -o error hamming.o bm.o bv.o error.o -lm

entropy: hamming.o bm.o bv.o entropy.o
	$(CC) -o entropy hamming.o bm.o bv.o entropy.o -lm

encode.o: 
	$(CC) $(CFLAGS) -c encode.c

decode.o:
	$(CC) $(CFLAGS) -c decode.c

entropy.o:
	$(CC) $(CFLAGS) -c entropy.c

error.o:
	$(CC) $(CFLAGS) -c error.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f encode decode error entropy bv.o bm.o hamming.o error.o entropy.o decode.o encode.o

scan-build: clean
	scan-build make
