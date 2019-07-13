# Configure build
include Configuration

EXE_NAMES=bubble insert heap merge merge_hybrid quick count radix network test benchmark benchmark_quick_partition

BUILD_EXE_PATHS=$(addprefix $(BUILD_DIR_PATH)/, $(addsuffix $(EXE_SUFFIX), $(EXE_NAMES)))

# Projects
all: $(BUILD_EXE_PATHS)

# If we depend on $(BUILD_DIR_PATH) for each sort, we modify its timestamp and make link everything again
BUILD_PROJECT_DEPENDENCIES=$(filter-out $(wildcard $(BUILD_DIR_PATH)), $(BUILD_DIR_PATH)) Configuration
BUILD_MODULE_DEPENDENCIES=Configuration

# Bubble sort
BUBBLE_MODULE=$(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/bubble_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/bubble$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(BUBBLE_MODULE)
	$(CC) -o $@ $(BUBBLE_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/bubble_main.o: bubble_sort.h debug.h bubble_main.c
$(BUILD_DIR_PATH)/bubble_sort.o: bubble_sort.h bubble_sort.c

# Insert sort
INSERT_MODULE=$(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/insert_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/insert$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(INSERT_MODULE)
	$(CC) -o $@ $(INSERT_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/insert_main.o: insert_sort.h debug.h insert_main.c
$(BUILD_DIR_PATH)/insert_sort.o: insert_sort.h insert_sort.c

# Heap sort
HEAP_MODULE=$(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/heap_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/heap$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(HEAP_MODULE)
	$(CC) -o $@ $(HEAP_MODULE) $(LDFLAGS)

$(BUILD_DIR_PATH)/heap_main.o: heap_sort.h debug.h heap_main.c
$(BUILD_DIR_PATH)/heap_sort.o: heap_sort.h heap_sort.c

# Merge sort
MERGE_MODULES=$(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/merge_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/merge$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MERGE_MODULES)
	$(CC) -o $@ $(MERGE_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/merge_main.o: merge_sort.h debug.h merge_main.c
$(BUILD_DIR_PATH)/merge_sort.o: merge_sort.h merge_sort.c

# Merge hybrid sort
MERGE_HYBRID_MODULES=$(BUILD_DIR_PATH)/merge_hybrid_sort.o $(BUILD_DIR_PATH)/merge_hybrid_main.o $(BUILD_DIR_PATH)/network_sort.o $(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/merge_hybrid$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MERGE_HYBRID_MODULES)
	$(CC) -o $@ $(MERGE_HYBRID_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/merge_hybrid_main.o: merge_hybrid_sort.h debug.h merge_hybrid_main.c
$(BUILD_DIR_PATH)/merge_hybrid_sort.o: merge_hybrid_sort.h merge_hybrid_sort.c

# Quick sort
QUICK_MODULES=$(BUILD_DIR_PATH)/quick_sort.o $(BUILD_DIR_PATH)/quick_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/quick$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(QUICK_MODULES)
	$(CC) -o $@ $(QUICK_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/quick_main.o: quick_sort.h debug.h quick_main.c
$(BUILD_DIR_PATH)/quick_sort.o: quick_sort.h quick_sort.c

# Count sort
COUNT_MODULES=$(BUILD_DIR_PATH)/count_sort.o $(BUILD_DIR_PATH)/count_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/count$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(COUNT_MODULES)
	$(CC) -o $@ $(COUNT_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/quick_main.o: count_sort.h debug.h count_main.c
$(BUILD_DIR_PATH)/quick_sort.o: count_sort.h count_sort.c

# Radix sort
RADIX_MODULES=$(BUILD_DIR_PATH)/radix_sort.o $(BUILD_DIR_PATH)/radix_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/radix$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(RADIX_MODULES)
	$(CC) -o $@ $(RADIX_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/radix_main.o: radix_sort.h debug.h radix_main.c
$(BUILD_DIR_PATH)/radix_sort.o: radix_sort.h radix_sort.c

# Network sort
NETWORK_MODULES=$(BUILD_DIR_PATH)/network_sort.o $(BUILD_DIR_PATH)/network_main.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/network$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(NETWORK_MODULES)
	$(CC) -o $@ $(NETWORK_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/network_main.o: network_sort.h debug.h network_main.c
$(BUILD_DIR_PATH)/network_sort.o: network_sort.h network_sort.c

# Test
ALL_SORT_HEADERS=bubble_sort.h insert_sort.h heap_sort.h merge_sort.h merge_hybrid_sort.h quick_sort.h count_sort.h radix_sort.h
ALL_SORT_MODULES=$(BUILD_DIR_PATH)/bubble_sort.o $(BUILD_DIR_PATH)/insert_sort.o $(BUILD_DIR_PATH)/heap_sort.o $(BUILD_DIR_PATH)/merge_sort.o $(BUILD_DIR_PATH)/merge_hybrid_sort.o $(BUILD_DIR_PATH)/quick_sort.o $(BUILD_DIR_PATH)/count_sort.o $(BUILD_DIR_PATH)/radix_sort.o $(BUILD_DIR_PATH)/network_sort.o
MAIN_TEST_MODULES=$(ALL_SORT_MODULES) $(BUILD_DIR_PATH)/main_test.o $(BUILD_DIR_PATH)/test.o $(BUILD_DIR_PATH)/debug.o $(BUILD_DIR_PATH)/option.o
$(BUILD_DIR_PATH)/test$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MAIN_TEST_MODULES)
	$(CC) -o $@ $(MAIN_TEST_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/main_test.o: $(ALL_SORT_HEADERS) test.h debug.h main_test.c
$(BUILD_DIR_PATH)/test.o: test.h test_template.h test.c test_template.c
$(BUILD_DIR_PATH)/debug.o: debug.h debug.c

# Benchmark
MAIN_BENCHMARK_MODULES=$(ALL_SORT_MODULES) $(BUILD_DIR_PATH)/main_benchmark.o $(BUILD_DIR_PATH)/benchmark.o $(BUILD_DIR_PATH)/std_sort.o $(BUILD_DIR_PATH)/option.o $(BUILD_DIR_PATH)/test.o $(BUILD_DIR_PATH)/debug.o
MAIN_BENCHMARK_LDFLAGS=$(LDFLAGS)
ifneq ($(DETECTED_TARGET)_$(COMPILER), MSVC_CLANG)
	MAIN_BENCHMARK_LDFLAGS:=$(MAIN_BENCHMARK_LDFLAGS) -lstdc++
endif
$(BUILD_DIR_PATH)/benchmark$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MAIN_BENCHMARK_MODULES)
	$(CC) -o $@ $(MAIN_BENCHMARK_MODULES) $(MAIN_BENCHMARK_LDFLAGS)

$(BUILD_DIR_PATH)/main_benchmark.o: $(ALL_SORT_HEADERS) benchmark.h std_sort.h debug.h main_benchmark.c
$(BUILD_DIR_PATH)/benchmark.o: benchmark.h benchmark.c
$(BUILD_DIR_PATH)/std_sort.o: std_sort.h std_sort.cpp
$(BUILD_DIR_PATH)/option.o: option.h option.c

# Benchmark Quick Partition
MAIN_BENCHMARK_QUICK_PARTITION_MODULES=$(BUILD_DIR_PATH)/quick_sort.o $(BUILD_DIR_PATH)/benchmark_quick_partition.o $(BUILD_DIR_PATH)/benchmark.o $(BUILD_DIR_PATH)/option.o $(BUILD_DIR_PATH)/debug.o
$(BUILD_DIR_PATH)/benchmark_quick_partition$(EXE_SUFFIX): $(BUILD_PROJECT_DEPENDENCIES) $(MAIN_BENCHMARK_QUICK_PARTITION_MODULES)
	$(CC) -o $@ $(MAIN_BENCHMARK_QUICK_PARTITION_MODULES) $(LDFLAGS)

$(BUILD_DIR_PATH)/benchmark_quick_partition.o: $(ALL_SORT_HEADERS) benchmark.h debug.h benchmark_quick_partition.c
$(BUILD_DIR_PATH)/benchmark.o: benchmark.h benchmark.c
$(BUILD_DIR_PATH)/option.o: option.h option.c

# Deploy (we assume updated binaries and don't build nor link anything
DEPLOY_EXE_PATHS=$(EXE_NAMES)
DEPLOY_EXE_TARGETS=$(addprefix deploy_, $(EXE_NAMES))
deploy: $(DEPLOY_EXE_TARGETS)

deploy_bubble:
	cp $(BUILD_DIR_PATH)/bubble$(EXE_SUFFIX) bubble

deploy_insert:
	cp $(BUILD_DIR_PATH)/insert$(EXE_SUFFIX) insert

deploy_heap:
	cp $(BUILD_DIR_PATH)/heap$(EXE_SUFFIX) heap

deploy_merge:
	cp $(BUILD_DIR_PATH)/merge$(EXE_SUFFIX) merge

deploy_merge_hybrid:
	cp $(BUILD_DIR_PATH)/merge_hybrid$(EXE_SUFFIX) merge_hybrid

deploy_quick:
	cp $(BUILD_DIR_PATH)/quick$(EXE_SUFFIX) quick

deploy_count:
	cp $(BUILD_DIR_PATH)/count$(EXE_SUFFIX) count

deploy_radix:
	cp $(BUILD_DIR_PATH)/radix$(EXE_SUFFIX) radix

deploy_network:
	cp $(BUILD_DIR_PATH)/network$(EXE_SUFFIX) network

deploy_test:
	cp $(BUILD_DIR_PATH)/test$(EXE_SUFFIX) test

deploy_benchmark:
	cp $(BUILD_DIR_PATH)/benchmark$(EXE_SUFFIX) benchmark

deploy_benchmark_quick_partition:
	cp $(BUILD_DIR_PATH)/benchmark_quick_partition$(EXE_SUFFIX) benchmark_quick_partition

# Inlining validation
LLVM_BC_FILES=$(wildcard $(BUILD_DIR_PATH)/*.bc)
LLVM_LL_FILES=$(LLVM_BC_FILES:.bc=.ll)
validate: $(LLVM_LL_FILES)

# Build rules
$(BUILD_DIR_PATH)/%.o: %.c $(BUILD_MODULE_DEPENDENCIES)
	$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR_PATH)/%.o: %.cpp $(BUILD_MODULE_DEPENDENCIES)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(BUILD_DIR_PATH)/%.ll: $(BUILD_DIR_PATH)/%.bc
	llvm-dis $<

$(BUILD_DIR_PATH):
	mkdir -p $(BUILD_DIR_PATH)

# Phony
.PHONY: deploy clean $(DEPLOY_EXE_TARGETS)

# Clean
clean:
	rm -rf *_clang_*
	rm -rf *_clangcl_*
	rm -rf *_gcc_*	
	rm -rf .release* .debug* .profile*
	rm -rf $(DEPLOY_EXE_PATHS) *.exe
