#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "benchmark.h"
#include "debug.h"

#include "insert_sort.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "std_sort.h"

typedef void (*sort_function_t)(int* keys, const int key_count, int* temp_keys);

void wrap_insert_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  insert_sort(keys, key_count);
}

void wrap_std_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  std_sort(keys, key_count);
}

void wrap_heap_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  heap_sort(keys, key_count);
}

void wrap_merge_sort(int* keys, const int key_count, int* temp_keys)
{
  merge_sort(keys, key_count, temp_keys);
}

void wrap_quick_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  quick_sort(keys, key_count, quick_median3_pivot_index);
}

void wrap_radix_sort(int* keys, const int key_count, int* temp_keys)
{
  radix_sort(keys, key_count, temp_keys);
}

typedef struct
{
  sort_function_t sort_function;
  const char* sort_name;
}
benchmark_t;

int main()
{
  const int key_count = 1000000;
  const int repeat_count = 20;
  int* ref_keys = (int*)malloc(key_count * sizeof(int));
  int* temp_keys = (int*)malloc(key_count * sizeof(int));
  int* keys = (int*)malloc(key_count * sizeof(int));

  benchmark_generate_random_keys(ref_keys, key_count, 42, INT_MIN, INT_MAX);

  benchmark_t benchmarks[] =
  {
    {wrap_std_sort, "std_sort"},
    {wrap_heap_sort, "heap_sort"},
    {wrap_merge_sort, "merge_sort"},
    {wrap_quick_sort, "quick_sort"},
    {wrap_radix_sort, "radix_sort"}
  };
  
  const int sort_count = sizeof(benchmarks) / sizeof(benchmarks[0]);
  
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    const benchmark_t benchmark = benchmarks[sort_index];
    const sort_function_t sort_function = benchmark.sort_function;
    const char* sort_name = benchmark.sort_name;

    int duration = 0;
    for (int repeat = 0; repeat < repeat_count; ++repeat)
    {
      memcpy(keys, ref_keys, key_count * sizeof(int));

      benchmark_scope_t* scope1 = benchmark_begin();
      sort_function(keys, key_count, temp_keys);
      duration += benchmark_end_us(scope1);
    }

    printf("Function %s took %d us\n", sort_name, duration / repeat_count);
  }

  free(keys);
  free(temp_keys);
  free(ref_keys);

  return 0;
}
