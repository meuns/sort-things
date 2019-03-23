# Configure build
include Configuration

# Projects
all: bubble$(EXE_SUFFIX) insert$(EXE_SUFFIX) heap$(EXE_SUFFIX) merge$(EXE_SUFFIX) quick$(EXE_SUFFIX) count$(EXE_SUFFIX) radix$(EXE_SUFFIX) test$(EXE_SUFFIX) benchmark$(EXE_SUFFIX)

# If we depend on $(BUILD_DIR_PATH) for each sort, we modify its timestamp and make link everything again
BUILD_PROJECT_DEPENDENCIES=$(filter-out $(wildcard $(BUILD_DIR_PATH)), $(BUILD_DIR_PATH)) Configuration
BUILD_MODULE_DEPENDENCIES=Configuration

# Bubble sort
BUBBLE_MODULE=$(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/bubble_main.o $(BUILD_DIR_PATH)/debug.o
bubble$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(BUBBLE_MODULE)
	$(CC) -o $@ $(BUBBLE_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/bubble_main.o: bubble_sort.h debug.h bubble_main.c
$(BUILD_DIR_PATH)/bubble_sort.o: bubble_sort.h bubble_sort.c

# Insert sort
INSERT_MODULE=$(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/insert_main.o $(BUILD_DIR_PATH)/debug.o
insert$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(INSERT_MODULE)
	$(CC) -o $@ $(INSERT_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/insert_main.o: insert_sort.h debug.h insert_main.c
$(BUILD_DIR_PATH)/insert_sort.o: insert_sort.h insert_sort.c

# Heap sort
HEAP_MODULE=$(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/heap_main.o $(BUILD_DIR_PATH)/debug.o
heap$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(HEAP_MODULE)
	$(CC) -o $@ $(HEAP_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/heap_main.o: heap_sort.h debug.h heap_main.c
$(BUILD_DIR_PATH)/heap_sort.o: heap_sort.h heap_sort.c

# Merge sort
MERGE_MODULES=$(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/merge_main.o $(BUILD_DIR_PATH)/debug.o
merge$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MERGE_MODULES)
	$(CC) -o $@ $(MERGE_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/merge_main.o: merge_sort.h debug.h merge_main.c
$(BUILD_DIR_PATH)/merge_sort.o: merge_sort.h merge_sort.c

# Quick sort
QUICK_MODULES=$(BUILD_DIR_PATH)/quick_sort.o $(BUILD_DIR_PATH)/quick_main.o $(BUILD_DIR_PATH)/debug.o
quick$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(QUICK_MODULES)
	$(CC) -o $@ $(QUICK_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/quick_main.o: quick_sort.h debug.h quick_main.c
$(BUILD_DIR_PATH)/quick_sort.o: quick_sort.h quick_sort.c

# Count sort
COUNT_MODULES=$(BUILD_DIR_PATH)/count_sort.o $(BUILD_DIR_PATH)/count_main.o $(BUILD_DIR_PATH)/debug.o
count$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(COUNT_MODULES)
	$(CC) -o $@ $(COUNT_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/quick_main.o: count_sort.h debug.h count_main.c
$(BUILD_DIR_PATH)/quick_sort.o: count_sort.h count_sort.c

# Radix sort
RADIX_MODULES=$(BUILD_DIR_PATH)/radix_sort.o $(BUILD_DIR_PATH)/radix_main.o $(BUILD_DIR_PATH)/debug.o
radix$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(RADIX_MODULES)
	$(CC) -o $@ $(RADIX_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/radix_main.o: radix_sort.h debug.h radix_main.c
$(BUILD_DIR_PATH)/radix_sort.o: radix_sort.h radix_sort.c

# Test
ALL_SORT_HEADERS=bubble_sort.h insert_sort.h heap_sort.h merge_sort.h quick_sort.h count_sort.h radix_sort.h
ALL_SORT_MODULES=$(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/quick_sort.o $(BUILD_DIR_PATH)/count_sort.o $(BUILD_DIR_PATH)/radix_sort.o

MAIN_TEST_MODULES=$(ALL_SORT_MODULES) $(BUILD_DIR_PATH)/main_test.o $(BUILD_DIR_PATH)/test.o $(BUILD_DIR_PATH)/debug.o
test$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MAIN_TEST_MODULES)
	$(CC) -o $@ $(MAIN_TEST_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/main_test.o: $(ALL_SORT_HEADERS) test.h debug.h main_test.c
$(BUILD_DIR_PATH)/test.o: test.h test_template.h test.c test_template.c
$(BUILD_DIR_PATH)/debug.o: debug.h debug.c

# Benchmark
MAIN_BENCHMARK_MODULES=$(ALL_SORT_MODULES) $(BUILD_DIR_PATH)/main_benchmark.o $(BUILD_DIR_PATH)/benchmark.o $(BUILD_DIR_PATH)/std_sort.o $(BUILD_DIR_PATH)/test.o $(BUILD_DIR_PATH)/debug.o
benchmark$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MAIN_BENCHMARK_MODULES)
	$(CC) -o $@ $(MAIN_BENCHMARK_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/main_benchmark.o: $(ALL_SORT_HEADERS) benchmark.h std_sort.h debug.h main_benchmark.c
$(BUILD_DIR_PATH)/benchmark.o: benchmark.h benchmark.c
$(BUILD_DIR_PATH)/std_sort.o: std_sort.h std_sort.cpp

# Build rules
$(BUILD_DIR_PATH)/%.o: %.c $(BUILD_MODULE_DEPENDENCIES)
	$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR_PATH)/%.o: %.cpp $(BUILD_MODULE_DEPENDENCIES)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(BUILD_DIR_PATH):
	mkdir -p $(BUILD_DIR_PATH)

clean:
	rm -f bubble insert heap merge quick count radix test benchmark
	rm -f bubble_d insert_d heap_d merge_d quick_d count_d radix_d test_d benchmark_d
	rm -f bubble_lto insert_lto heap_lto merge_lto quick_lto count_lto radix_lto test_lto benchmark_lto
	rm -f .release/*.o .debug/*.o
	rm -f .release_lto/*.o .debug_lto/*.o
	rm -rf .release .debug
	rm -rf .release_lto .debug_lto	
