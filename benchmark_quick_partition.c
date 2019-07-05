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

typedef void (*wrap_quick_partition_t)(int* const keys_begin, int* const keys_end);

void wrap_quick_partition_default(int* const keys_begin, int* const keys_end)
{
  quick_partition_default(keys_begin, keys_end, quick_median3_pivot(keys_begin, keys_end));
}

void wrap_quick_partition_swap_then_fit(int* const keys_begin, int* const keys_end)
{
  quick_partition_swap_then_fit(keys_begin, keys_end, quick_median3_pivot(keys_begin, keys_end));
}

void wrap_quick_partition_three_ways(int* const keys_begin, int* const keys_end)
{
  quick_partition_three_ways(keys_begin, keys_end, quick_median3_pivot(keys_begin, keys_end));
}

typedef struct
{
  wrap_quick_partition_t quick_partition;
  const char* partition_name;
  long long int is_enabled;
}
benchmark_t;

int main(int argc, char** argv)
{
  const int quick_partition_group_is_enabled = option_parse_command_line(argc, argv, "--quick-partition=", "-qp=", 0);

  const benchmark_t benchmarks[] =
  {
    {wrap_quick_partition_default, "quick_sort_default_median3", quick_partition_group_is_enabled || option_parse_command_line(argc, argv, "--quick-partition-default=", "-qpd=", 0)},    
    {wrap_quick_partition_swap_then_fit, "quick_sort_swap_then_fit_median3", quick_partition_group_is_enabled || option_parse_command_line(argc, argv, "--quick-partition-swap-then-fit=", "-qpsf=", 0)},    
    {wrap_quick_partition_three_ways, "quick_sort_three_ways_median3", quick_partition_group_is_enabled || option_parse_command_line(argc, argv, "--quick-partition-three-ways=", "-qp3=", 0)},
  };

  const int max_key_count = option_parse_command_line(argc, argv, "--max-key-count=", "-kc=", 1 << 24);
  const int min_key_count = option_parse_command_line(argc, argv, "--min-key-count=", "-mkc=", max_key_count);
  const int step_key_count = option_parse_command_line(argc, argv, "--step-key=", "-sk=", 1 << 10);
  const int max_key_value = option_parse_command_line(argc, argv, "--max-key-value=", "-kv=", INT_MAX);
  const int min_key_value = option_parse_command_line(argc, argv, "--min-key-value=", "-mkv=", INT_MIN);
  const int split_count = option_parse_command_line(argc, argv, "--split-count", "-sc=", 1);
  const int verbose = option_parse_command_line(argc, argv, "--verbose=", "-v=", 1);
  const int repeat_count = 20;

  int* ref_keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  int* temp_keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  int* keys = (int*)malloc((unsigned int)max_key_count * sizeof(int));
  benchmark_generate_random_keys(ref_keys, max_key_count, 42, min_key_value, max_key_value);

  const int sort_count = sizeof(benchmarks) / sizeof(benchmarks[0]);
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    const benchmark_t benchmark = benchmarks[sort_index];
    if (benchmark.is_enabled == 0)
    {
      continue;
    }

    const wrap_quick_partition_t quick_partition = benchmark.quick_partition;
    const char* partition_name = benchmark.partition_name;

    if (!verbose)
    {
      printf("Partition Name;Key Count;Duration us\n");
    }

    for (int key_count = min_key_count; key_count <= max_key_count; key_count += step_key_count)
    {
      const int split_key_count = key_count / split_count;

      if (verbose)
      {
        printf("Function %s count %d split %d:\n", partition_name, key_count, split_count);
      }     

      int duration = 0;

      for (int repeat_index = 0; repeat_index < repeat_count; ++repeat_index)
      {
        if (verbose)
        {
          printf("  %.3d", repeat_index);
        }

        memcpy(keys, ref_keys, (unsigned int)key_count * sizeof(int));

        {
          int repeat_duration = 0;
          benchmark_scope_t* inner_scope1 = benchmark_begin();
          for (int split_index = 0; split_index < split_count; ++split_index)
          {
            quick_partition(&keys[split_index * split_key_count], &keys[split_index * split_key_count + split_key_count]);
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
        printf("%s;%d;%d\n", partition_name, key_count, average_duration);
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
