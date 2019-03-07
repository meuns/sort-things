#include "quick_sort.h"
#include <stdio.h>

__attribute__((always_inline))
static inline int quick_pivot_index(int* keys __attribute__((unused)), const int key_count)
{
  return key_count >> 1;
}

__attribute__((always_inline))
static inline int quick_partition(int* keys, const int key_count, const int pivot_index, const int pivot_key)
{
  keys[pivot_index] = keys[0];
  //keys[0] = -666;
  
  int left_index = 1;
  int left_key = keys[left_index];
  
  int right_index = key_count - 1;
  int right_key = keys[right_index];
  
  const int last_index = right_index;
  
  while (right_key >= pivot_key && right_index > 0)
  {
    right_index = right_index - 1;
    right_key = keys[right_index];
  }
  
  while (left_key < pivot_key && left_index < last_index)
  {
    keys[left_index - 1] = left_key;
    left_index = left_index + 1;
    left_key = keys[left_index];      
  }
  
  while (left_index < right_index)
  {
    keys[right_index] = left_key;
    //keys[left_index] = -666;
    keys[left_index - 1] = right_key;
    
    right_index = right_index - 1;
    right_key = keys[right_index];
    left_index = left_index + 1;
    left_key = keys[left_index];
    
    while (right_key >= pivot_key && right_index > 0)
    {
      right_index = right_index - 1;
      right_key = keys[right_index];
    }
    
    while (left_key < pivot_key && left_index < last_index)
    {
      keys[left_index - 1] = left_key;
      left_index = left_index + 1;
      left_key = keys[left_index];      
    }
  }
  
  if (left_index == 1)
  {
    keys[left_index - 1] = left_key;
  }
  
  keys[right_index] = pivot_key;
  
  return right_index;
}

__attribute__((noinline))
void quick_sort(int* base_keys, const int key_count)
{
  const int stack_size = 32;
  int* stack_keys[stack_size];
  int stack_key_count[stack_size];
  int stack_top = -1;
  
  stack_top = stack_top + 1;
  stack_keys[stack_top] = base_keys;
  stack_key_count[stack_top] = key_count;
  
  while (stack_top > -1)
  {
    int* keys = stack_keys[stack_top];
    const int key_count = stack_key_count[stack_top];
    stack_top = stack_top - 1;

    const int pivot_index = quick_pivot_index(keys, key_count);
    const int pivot_key = keys[pivot_index];
    const int partition_index = quick_partition(keys, key_count, pivot_index, pivot_key);

    const int left_key_count = partition_index;
    if (left_key_count > 1)
    {
      stack_top = stack_top + 1;
      stack_keys[stack_top] = keys;
      stack_key_count[stack_top] = left_key_count;
    }

    const int right_key_count = key_count - (left_key_count + 1);
    if (right_key_count > 1)
    {
      stack_top = stack_top + 1;
      stack_keys[stack_top] = keys + (left_key_count + 1);
      stack_key_count[stack_top] = right_key_count;
    }
  }
}
