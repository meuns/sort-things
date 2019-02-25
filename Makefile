CC=clang
CFLAGS=-W -Wall -std=c11 -pedantic
LDFLAGS=

all: bubble

bubble: bubble_sort.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: bubble_sort.h main.c
bubble_sort.o: bubble_sort.h bubble_sort.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bubble *.o
