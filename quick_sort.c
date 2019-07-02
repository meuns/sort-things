#include "quick_sort.h"

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE int* quick_middle_pivot(int* const keys_begin, int* const keys_end)
{
  return keys_begin + ((keys_end - keys_begin) >> 1);
}

__attribute__((always_inline))
WA_INLINE int* quick_median3_pivot(int* const keys_begin, int* const keys_end)
{
  int* low_key_it = keys_begin;
  int* mid_key_it = quick_middle_pivot(keys_begin, keys_end);
  int* high_key_it = keys_end - 1;

  if (*mid_key_it > *high_key_it)
  {
    int* temp = mid_key_it;
    mid_key_it = high_key_it;
    high_key_it = temp;
  }

  if (*low_key_it > *high_key_it)
  {
    low_key_it = high_key_it;
  }

  if (*low_key_it > *mid_key_it)
  {
    mid_key_it = low_key_it;
  }

  return mid_key_it;
}

typedef struct
{
  int* left_dutch_end;
  int* right_dutch_begin;
}
quick_partition_result_t;

__attribute__((always_inline))
static inline quick_partition_result_t quick_partition(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  const int pivot_key = *pivot_key_it;
  *pivot_key_it = *keys_begin;

  int* left_it = keys_begin + 1;
  int* right_it = keys_end - 1;
  
  while (right_it > left_it)
  {
    while (right_it > left_it && *right_it >= pivot_key)
    {
      right_it--;
    }
    
    while (right_it > left_it && *left_it < pivot_key)
    {
      left_it++;
    }

    if (right_it > left_it)
    {
      int right_key = *right_it;
      *right_it = *left_it;
      *left_it = right_key;

      right_it--;
      left_it++;
    }
  }

  int* new_pivot_it = right_it;
  if (*right_it >= pivot_key)
  {
    new_pivot_it--;
  }

  *keys_begin = *new_pivot_it;
  *new_pivot_it = pivot_key;
  
  left_it = new_pivot_it;
  if (left_it > keys_begin)
  {
    left_it--;
    while (left_it > keys_begin && *left_it == pivot_key)
    {
      left_it--;
    }
  }

  right_it = new_pivot_it;
  if (right_it < keys_end)
  {
    right_it++;
    while (right_it < keys_end && *right_it == pivot_key)
    {
      right_it++;
    }
  }

  quick_partition_result_t result;
  result.left_dutch_end = left_it + 1;
  result.right_dutch_begin = right_it;
  return result;
}

typedef struct
{
  int* keys_begin;
  int* keys_end;
}
stack_element_t;

__attribute__((always_inline))
void quick_sort(int* const base_keys, const int base_key_count, const quick_pivot_t quick_pivot)
{
  if (base_key_count < 2)
  {
    return;
  }

  const int stack_size = 32;
  stack_element_t stack[stack_size];
  const stack_element_t* const stack_begin = stack;
  stack_element_t* stack_top_it = stack;
  *stack_top_it = (stack_element_t){base_keys, base_keys + base_key_count};
  
  while (stack_top_it >= stack_begin)
  {
    const stack_element_t stack_element = *stack_top_it--;
    int* const keys_begin = stack_element.keys_begin;
    int* const keys_end = stack_element.keys_end;

    const quick_partition_result_t result = quick_partition(keys_begin, keys_end, quick_pivot(keys_begin, keys_end));
    int* const left_dutch_end = result.left_dutch_end;
    int* const right_dutch_begin = result.right_dutch_begin;
    const int left_key_count = (int)(left_dutch_end - keys_begin);
    const int right_key_count = (int)(keys_end - right_dutch_begin);

    if (left_key_count > right_key_count)
    {
      if (left_key_count > 1)
      {
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
      
      if (right_key_count > 1)
      {
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }
    }
    else
    {
      if (right_key_count > 1)
      {
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }

      if (left_key_count > 1)
      {
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
    }
  }
}
