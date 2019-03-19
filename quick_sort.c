#include "quick_sort.h"

#include <stdio.h>

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE int quick_middle_pivot_index(int* keys __attribute__((unused)), const int key_count)
{
  return key_count >> 1;
}

__attribute__((always_inline))
WA_INLINE int quick_median3_pivot_index(int* keys, const int key_count)
{
  int low_index = 0;
  int mid_index = key_count >> 1;
  int high_index = key_count - 1;
  
  int low_key = keys[low_index];
  int mid_key = keys[mid_index];    
  int high_key = keys[high_index];

  if (mid_key > high_key)
  {
    const int temp_key = mid_key;
    mid_key = high_key;
    high_key = temp_key;

    const int temp_index = mid_index;
    mid_index = high_index;
    high_index = temp_index;
  }

  if (low_key > high_key)
  {
    low_key = high_key;    
    low_index = high_index;
  }

  if (low_key > mid_key)
  {
    mid_index = low_index;
  }

  return mid_index;
}

typedef struct
{
  int left_dutch_index;
  int right_dutch_index;
}
quick_partition_result_t;

__attribute__((always_inline))
static inline quick_partition_result_t quick_partition(int* keys, const int key_count, const int pivot_index, const int pivot_key)
{
  keys[pivot_index] = keys[0];

  int left_index = 1;
  int left_key = keys[left_index];
  
  int right_index = key_count - 1;
  int right_key = keys[right_index];
  
  while (right_key >= pivot_key && right_index > left_index)
  {
    right_index = right_index - 1;
    right_key = keys[right_index];
  }
  
  while (left_key < pivot_key && right_index > left_index)
  {
    left_index = left_index + 1;
    left_key = keys[left_index];      
  }

  while (left_index < right_index)
  {
    keys[right_index] = left_key;    
    keys[left_index] = right_key;

    right_index = right_index - 1;
    right_key = keys[right_index];
    left_index = left_index + 1;
    left_key = keys[left_index];

    while (right_key >= pivot_key && right_index > left_index)
    {
      right_index = right_index - 1;
      right_key = keys[right_index];
    }
    
    while (left_key < pivot_key && right_index > left_index)
    {
      left_index = left_index + 1;
      left_key = keys[left_index];      
    }
  }

  int new_pivot_index = right_index;    
  if (right_key >= pivot_key && new_pivot_index > 0)
  {
    new_pivot_index = new_pivot_index - 1;
  }

  keys[0] = keys[new_pivot_index];
  keys[new_pivot_index] = pivot_key;

  left_index = new_pivot_index;
  left_key = pivot_key;
  while (left_key == pivot_key && left_index > 0)
  {
    left_index = left_index - 1;
    left_key = keys[left_index];
  }

  right_index = new_pivot_index;
  right_key = pivot_key;
  while (right_key == pivot_key && right_index < key_count)
  {
    right_index = right_index + 1;
    right_key = keys[right_index];
  }

  quick_partition_result_t result;
  result.left_dutch_index = left_index;
  result.right_dutch_index = right_index;
  return result;
}

__attribute__((noinline))
void quick_sort(int* base_keys, const int base_key_count, const quick_pivot_index_t quick_pivot_index)
{
  const int stack_size = 32;
  int* stack_keys[stack_size];
  int stack_key_count[stack_size];
  int stack_top = -1;
  
  stack_top = stack_top + 1;
  stack_keys[stack_top] = base_keys;
  stack_key_count[stack_top] = base_key_count;
  
  while (stack_top > -1)
  {
    int* keys = stack_keys[stack_top];
    const int key_count = stack_key_count[stack_top];
    stack_top = stack_top - 1;

    const int pivot_index = quick_pivot_index(keys, key_count);
    const int pivot_key = keys[pivot_index];
    
    const quick_partition_result_t result = quick_partition(keys, key_count, pivot_index, pivot_key);

    const int left_key_count = result.left_dutch_index + 1;
    if (left_key_count > 1)
    {
      stack_top = stack_top + 1;
      stack_keys[stack_top] = keys;
      stack_key_count[stack_top] = left_key_count;
    }

    const int right_key_count = key_count - result.right_dutch_index;
    if (right_key_count > 1)
    {
      stack_top = stack_top + 1;
      stack_keys[stack_top] = keys + result.right_dutch_index;
      stack_key_count[stack_top] = right_key_count;
    }
  }
}
