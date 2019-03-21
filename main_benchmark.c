#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "benchmark.h"
#include "debug.h"

#include "heap_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"

typedef void (*sort_function_t)(int* keys, const int key_count, int* temp_keys);

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

int main()
{
  const int key_count = 1000000;
  int* ref_keys = (int*)malloc(key_count * sizeof(int));
  int* temp_keys = (int*)malloc(key_count * sizeof(int));
  int* keys = (int*)malloc(key_count * sizeof(int));

  benchmark_generate_random_keys(ref_keys, key_count, 42, INT_MIN, INT_MAX);

  sort_function_t sort_functions[] =
  {
    wrap_heap_sort,
    wrap_merge_sort,
    wrap_quick_sort,
    wrap_radix_sort
  };
  
  const int sort_count = sizeof(sort_functions) / sizeof(sort_functions[0]);
  
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    sort_function_t sort_function = sort_functions[sort_index];

    memcpy(keys, ref_keys, key_count * sizeof(int));
    
    benchmark_scope_t* scope1 = benchmark_begin();
    sort_function(keys, key_count, temp_keys);
    int duration = benchmark_end(scope1);

    printf("Function %d took %d ms\n", sort_index, duration);
  }

  free(keys);
  free(temp_keys);
  free(ref_keys);

  return 0;
}
