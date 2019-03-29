#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "benchmark.h"
#include "debug.h"

#include "bubble_sort.h"
#include "insert_sort.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "network_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "std_sort.h"

typedef void (*sort_function_t)(int* keys, const int key_count, int* temp_keys);

void wrap_network_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  network_sort(keys, key_count);
}

void wrap_bubble_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  bubble_sort(keys, key_count);
}

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

void wrap_radix_sort_halfbyte(int* keys, const int key_count, int* temp_keys)
{
  radix_sort_halfbyte(keys, key_count, temp_keys);
}

void wrap_radix_sort_byte(int* keys, const int key_count, int* temp_keys)
{
  radix_sort_byte(keys, key_count, temp_keys);
}

void wrap_radix_sort_short(int* keys, const int key_count, int* temp_keys)
{
  radix_sort_short(keys, key_count, temp_keys);
}

typedef struct
{
  sort_function_t sort_function;
  const char* sort_name;
  long long int is_enabled;
}
benchmark_t;

int check_option(int argc, char** argv, const char* long_option, const char* short_option, int default_value)
{
  const size_t long_length = strlen(long_option);
  const size_t short_length = strlen(short_option);

  for (int argument_index = 1; argument_index < argc; ++argument_index)
  {
    const char* argument = argv[argument_index];
    if (strstr(argument, long_option))
    {
      int value = strtol(&argument[long_length], NULL, 10);
      if (errno == 0)
      {
        return value;
      }
    }

    if (strstr(argument, short_option))
    {
      int value = strtol(&argument[short_length], NULL, 10);
      if (errno == 0)
      {
        return value;
      }
    }
  }

  return default_value;
}

int main(int argc, char** argv)
{
  const benchmark_t benchmarks[] =
  {
    {wrap_network_sort, "network_sort", check_option(argc, argv, "--network-sort=", "-ns=", 0)},
    {wrap_insert_sort, "bubble_sort", check_option(argc, argv, "--bubble-sort=", "-bs=", 0)},
    {wrap_insert_sort, "insert_sort", check_option(argc, argv, "--insert-sort=", "-is=", 0)},
    {wrap_heap_sort, "heap_sort", check_option(argc, argv, "--heap-sort=", "-hs=", 0)},
    {wrap_merge_sort, "merge_sort", check_option(argc, argv, "--merge-sort=", "-ms=", 0)},
    {wrap_quick_sort, "quick_sort", check_option(argc, argv, "--quick-sort=", "-qs=", 0)},
    {wrap_std_sort, "std_sort", check_option(argc, argv, "--std-sort=", "-ss=", 0)},
    {wrap_radix_sort_halfbyte, "radix_sort_halfbyte", check_option(argc, argv, "--radix-halfbyte-sort=", "-rhs=", 0)},
    {wrap_radix_sort_byte, "radix_sort_byte", check_option(argc, argv, "--radix-byte-sort=", "-rs=", 0)},
    {wrap_radix_sort_short, "radix_sort_short", check_option(argc, argv, "--radix-short-sort=", "-rss=", 0)}
  };

  const int key_count = 1000000;
  const int split_key_count = check_option(argc, argv, "--split-key-count=", "-s=", 1000);
  const int repeat_count = 20;
  int* ref_keys = (int*)malloc((unsigned int)key_count * sizeof(int));
  int* temp_keys = (int*)malloc((unsigned int)key_count * sizeof(int));
  int* keys = (int*)malloc((unsigned int)key_count * sizeof(int));

  benchmark_generate_random_keys(ref_keys, key_count, 42, INT_MIN, INT_MAX);
  
  const int sort_count = sizeof(benchmarks) / sizeof(benchmarks[0]);

  printf("Key Count %d Split %d\n", key_count, split_key_count);
  
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    const benchmark_t benchmark = benchmarks[sort_index];
    if (benchmark.is_enabled == 0)
    {
      continue;
    }

    const sort_function_t sort_function = benchmark.sort_function;
    const char* sort_name = benchmark.sort_name;
    const int split_count = key_count / split_key_count;

    int duration = 0;
    printf("Function %s count %d split %d :\n", sort_name, key_count, split_key_count);

    for (int repeat_index = 0; repeat_index < repeat_count; ++repeat_index)
    {
      printf("  %.3d", repeat_index);
      memcpy(keys, ref_keys, (unsigned int)key_count * sizeof(int));

      benchmark_scope_t* scope1 = benchmark_begin();      
      for (int split_index = 0; split_index < split_count; ++split_index)
      {
        sort_function(&keys[split_index * split_key_count], split_key_count, temp_keys);
      }      
      int repeat_duration = benchmark_end_us(scope1);

      printf(" %d us\n", repeat_duration);
      duration += repeat_duration;
    }

    printf("  took an average %d us\n", duration / repeat_count);
  }

  free(keys);
  free(temp_keys);
  free(ref_keys);

  return 0;
}
