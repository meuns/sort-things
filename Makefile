CC=clang

ifeq ($(DEBUG), 1)
	CFLAGS=-W -Wall -std=c11 -pedantic -g -O0
	LDFLAGS=
	BUILD_DIR_PATH=./.debug
	EXE_SUFFIX=_d
else
	CFLAGS=-W -Wall -std=c11 -pedantic -O2
	LDFLAGS=
	BUILD_DIR_PATH=./.release
	EXE_SUFFIX=
endif

all: build_dir bubble$(EXE_SUFFIX) insert$(EXE_SUFFIX) heap$(EXE_SUFFIX) merge$(EXE_SUFFIX) main_test$(EXE_SUFFIX)

.PHONY: clean build_dir

# Bubble sort
bubble$(EXE_SUFFIX): $(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/bubble_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR_PATH)/bubble_main.o: bubble_sort.h bubble_main.c
$(BUILD_DIR_PATH)/bubble_sort.o: bubble_sort.h bubble_sort.c

# Insert sort
insert$(EXE_SUFFIX): $(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/insert_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR_PATH)/insert_main.o: insert_sort.h insert_main.c
$(BUILD_DIR_PATH)/insert_sort.o: insert_sort.h insert_sort.c

# Heap sort
heap$(EXE_SUFFIX): $(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/heap_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR_PATH)/heap_main.o: heap_sort.h heap_main.c
$(BUILD_DIR_PATH)/heap_sort.o: heap_sort.h heap_sort.c

# Merge sort
merge$(EXE_SUFFIX): $(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/merge_main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR_PATH)/merge_main.o: merge_sort.h merge_main.c
$(BUILD_DIR_PATH)/merge_sort.o: merge_sort.h merge_sort.c

# Test
main_test$(EXE_SUFFIX): $(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/main_test.o $(BUILD_DIR_PATH)/test.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR_PATH)/main_test.o: bubble_sort.h insert_sort.h heap_sort.h merge_sort.h test.h main_test.c
$(BUILD_DIR_PATH)/test.o: test.h test.c

# Build rules
$(BUILD_DIR_PATH)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

build_dir:
	mkdir -p $(BUILD_DIR_PATH)

clean:
	rm -f bubble insert heap merge main_test bubble_d insert_d heap_d merge_d main_test_d .release/*.o .debug/*.o
	rm -rf .release .debug
