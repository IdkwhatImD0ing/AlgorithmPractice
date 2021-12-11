CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: banhammer 

banhammer: bf.o bv.o ht.o ll.o node.o parser.o speck.o banhammer.o
	$(CC) -o banhammer bf.o bv.o ht.o ll.o node.o parser.o speck.o banhammer.o -lm

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f banhammer banhammer.o bf.o bv.o ht.o ll.o node.o parser.o speck.o

scan-build: clean
	scan-build make
