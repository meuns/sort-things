#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "benchmark.h"
#include "debug.h"
#include "option.h"

#include "bubble_sort.h"
#include "insert_sort.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "merge_hybrid_sort.h"
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

void wrap_std_stable_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  std_stable_sort(keys, key_count);
}

void wrap_std_qsort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  std_qsort(keys, key_count);
}

void wrap_heap_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  heap_sort(keys, key_count);
}

__attribute__((always_inline))
int benchmark_compare_le_lto(const void* left_key, const void* right_key)
{
  const int* left_key_int = (const int*)left_key;
  const int* right_key_int = (const int*)right_key;
  return *left_key_int <= *right_key_int;
}

__attribute__((always_inline))
void benchmark_copy_lto(void* to_key, const void* from_key)
{
  int* to_key_int = (int*)to_key;
  const int* from_key_int = (const int*)from_key;
  *to_key_int = *from_key_int;
}

void wrap_merge_sort(int* keys, const int key_count, int* temp_keys)
{
  merge_sort(keys, key_count, temp_keys);
}

void wrap_merge_sort_hybrid(int* keys, const int key_count, int* temp_keys)
{
  merge_sort_hybrid(keys, key_count, temp_keys);
}

void wrap_quick_sort(int* keys, const int key_count, int* temp_keys __attribute__((unused)))
{
  quick_sort(keys, key_count, quick_median3_pivot);
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

int main(int argc, char** argv)
{
  const benchmark_t benchmarks[] =
  {
    {wrap_network_sort, "network_sort", option_parse_command_line(argc, argv, "--network-sort=", "-ns=", 0)},
    {wrap_insert_sort, "bubble_sort", option_parse_command_line(argc, argv, "--bubble-sort=", "-bs=", 0)},
    {wrap_insert_sort, "insert_sort", option_parse_command_line(argc, argv, "--insert-sort=", "-is=", 0)},
    {wrap_heap_sort, "heap_sort", option_parse_command_line(argc, argv, "--heap-sort=", "-hs=", 0)},
    {wrap_merge_sort, "merge_sort", option_parse_command_line(argc, argv, "--merge-sort=", "-ms=", 0)},
    {wrap_merge_sort_hybrid, "merge_sort_hybrid", option_parse_command_line(argc, argv, "--merge-sort-hybrid=", "-msh=", 0)},
    {wrap_quick_sort, "quick_sort", option_parse_command_line(argc, argv, "--quick-sort=", "-qs=", 0)},
    {wrap_std_sort, "std_sort", option_parse_command_line(argc, argv, "--std-sort=", "-std=", 0)},
    {wrap_std_stable_sort, "std_stable_sort", option_parse_command_line(argc, argv, "--std-stable-sort=", "-sts=", 0)},
    {wrap_std_qsort, "std_qsort", option_parse_command_line(argc, argv, "--std-qsort=", "-stq=", 0)},
    {wrap_radix_sort_halfbyte, "radix_sort_halfbyte", option_parse_command_line(argc, argv, "--radix-halfbyte-sort=", "-rsh=", 0)},
    {wrap_radix_sort_byte, "radix_sort_byte", option_parse_command_line(argc, argv, "--radix-byte-sort=", "-rs=", 0)},
    {wrap_radix_sort_short, "radix_sort_short", option_parse_command_line(argc, argv, "--radix-short-sort=", "-rss=", 0)}
  };

  const int max_key_power = option_parse_command_line(argc, argv, "--max-key-pow2=", "-kp=", 24);
  const int min_key_power = option_parse_command_line(argc, argv, "--min-key-pow2=", "-mkp=", max_key_power);
  const int step_key_power = option_parse_command_line(argc, argv, "--step-key-pow2=", "-skp=", 10);
  const int split_count = option_parse_command_line(argc, argv, "--split-count", "-sc=", 1);
  const int inner_scope = option_parse_command_line(argc, argv, "--inner-scope=", "-i=", 1);
  const int verbose = option_parse_command_line(argc, argv, "--verbose=", "-v=", 1);
  const int repeat_count = 20;

  const int min_key_count = 1 << min_key_power;
  const int max_key_count = 1 << max_key_power;
  const int step_key_count = 1 << step_key_power;

  int* ref_keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  int* temp_keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  int* keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  benchmark_generate_random_keys(ref_keys, max_key_count, 42, INT_MIN, INT_MAX);

  const int sort_count = sizeof(benchmarks) / sizeof(benchmarks[0]);
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    const benchmark_t benchmark = benchmarks[sort_index];
    if (benchmark.is_enabled == 0)
    {
      continue;
    }

    const sort_function_t sort_function = benchmark.sort_function;
    const char* sort_name = benchmark.sort_name;

    if (!verbose)
    {
      printf("Key count;Duration us\n");
    }

    for (int key_count = min_key_count; key_count <= max_key_count; key_count += step_key_count)
    {
      const int split_key_count = key_count / split_count;

      if (verbose)
      {
        printf("Function %s count %d split %d inner %d:\n", sort_name, key_count, split_count, inner_scope);
      }     

      int duration = 0;

      for (int repeat_index = 0; repeat_index < repeat_count; ++repeat_index)
      {
        if (verbose)
        {
          printf("  %.3d", repeat_index);
        }

        memcpy(keys, ref_keys, (unsigned int)key_count * sizeof(int));

        if (inner_scope)
        {
          int repeat_duration = 0;        
          for (int split_index = 0; split_index < split_count; ++split_index)
          {
            benchmark_scope_t* inner_scope1 = benchmark_begin();
            sort_function(&keys[split_index * split_key_count], split_key_count, temp_keys);
            repeat_duration += benchmark_end_us(inner_scope1);
          }
          
          if (verbose)
          {
            printf(" %dus\n", repeat_duration);
          }

          duration += repeat_duration;
        }
        else
        {
          int repeat_duration = 0;
          benchmark_scope_t* inner_scope1 = benchmark_begin();
          for (int split_index = 0; split_index < split_count; ++split_index)
          {
            sort_function(&keys[split_index * split_key_count], split_key_count, temp_keys);
          }
          repeat_duration += benchmark_end_us(inner_scope1);
          
          if (verbose)
          {
            printf(" %dus\n", repeat_duration);
          }

          duration += repeat_duration;
        }
      }

      const int average_duration = duration / repeat_count;
      if (verbose)
      {
        printf("  %d took an average %dus\n", key_count, average_duration);
      }
      else
      {
        printf("%d;%d\n", key_count, average_duration);
      }
    }
  }

  free(keys);
  free(temp_keys);
  free(ref_keys);

  if (verbose)
  {
    printf("Done !\n");
  }

  return 0;
}
