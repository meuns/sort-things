#pragma once

typedef int* (*quick_pivot_t)(int* const keys_begin, int* const keys_end);
int* quick_middle_pivot(int* const keys_begin, int* const keys_end);
int* quick_median3_pivot(int* const keys_begin, int* const keys_end);

typedef struct
{
  int* left_dutch_end;
  int* right_dutch_begin;
}
quick_partition_result_t;

typedef quick_partition_result_t (*quick_partition_t)(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_default(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_then_fit(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_8(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_16(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_32(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_64(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_128(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_swap_by_block_then_fit_256(int* const keys_begin, int* const keys_end, int* const pivot_key_it);
quick_partition_result_t quick_partition_three_ways(int* const keys_begin, int* const keys_end, int* const pivot_key_it);

void quick_sort(int* const keys, const int key_count, const quick_partition_t quick_partition, const quick_pivot_t quick_pivot);
