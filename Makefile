CC=clang
CFLAGS=-W -Wall -std=c11 -pedantic -g -O0
LDFLAGS=

all: bubble insert heap merge merge_test

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

merge: merge_sort.o merge_main.o test.o
	$(CC) -o $@ $^ $(LDFLAGS)

merge_test: merge_sort.o merge_test.o test.o
	$(CC) -o $@ $^ $(LDFLAGS)

merge_main.o: merge_sort.h merge_main.c
merge_test.o: merge_sort.h test.h merge_test.c
merge_sort.o: merge_sort.h merge_sort.c

test.o: test.h test.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bubble insert heap merge merge_test *.o
