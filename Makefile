CC=clang
CFLAGS=-W -Wall -std=c11 -pedantic -g -O0
LDFLAGS=

all: bubble insert heap

bubble: bubble_sort.o bubble_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

bubble_main.o: bubble_sort.h bubble_main.c
bubble_sort.o: bubble_sort.h bubble_sort.c

insert: insert_sort.o insert_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

insert_main.o: insert_sort.h insert_main.c
insert_sort.o: insert_sort.h insert_sort.c

heap: heap_sort.o heap_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

heap_main.o: heap_sort.h heap_main.c
heap_sort.o: heap_sort.h heap_sort.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bubble insert heap *.o
