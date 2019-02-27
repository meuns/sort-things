CC='/c/Program Files/LLVM/bin/clang'
CFLAGS=-W -Wall -std=c11 -pedantic
LDFLAGS=

all: bubble insert

bubble: bubble_sort.o bubble_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

bubble_main.o: bubble_sort.h bubble_main.c
bubble_sort.o: bubble_sort.h bubble_sort.c

insert: insert_sort.o insert_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

insert_main.o: insert_sort.h insert_main.c
insert_sort.o: insert_sort.h insert_sort.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bubble insert *.o
