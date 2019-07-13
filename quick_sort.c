#include "quick_sort.h"

#include "debug.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#if defined(WA_LINKING_INLINE_FUNCTION)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

#if defined(COMPILER_CLANG)
    #define PRAGMA_UNROLL _Pragma("unroll")
#else
    #define PRAGMA_UNROLL
#endif

__attribute__((always_inline))
WA_INLINE int* quick_middle_pivot(int* const keys_begin, int* const keys_end)
{
  return keys_begin + ((keys_end - keys_begin) >> 1);
}

__attribute__((always_inline))
WA_INLINE int* quick_median3_pivot(int* const keys_begin, int* const keys_end)
{
  assert(keys_begin);
    assert(keys_end);

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

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_default(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
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

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit(int* const keys_begin, int* const keys_end, int* const pivot_key_it, const int max_left_swap_count, const int max_right_swap_count)
{
  const int max_swap_count = max_left_swap_count + max_right_swap_count;
  int* left_swaps[max_swap_count];
  int* right_swaps[max_swap_count];

  const int pivot_key = *pivot_key_it;
  *pivot_key_it = *keys_begin;
  int* left_it = keys_begin + 1;
  int* right_it = keys_end - 1;

  int** const left_swaps_begin = left_swaps;
  int** const right_swaps_begin = right_swaps;

  while (right_it - left_it >= max_swap_count)
  {
    int** left_swap_it = left_swaps_begin;
    while (right_it - left_it >= max_swap_count && left_swap_it == left_swaps_begin)
    {
      int *left_block_begin = left_it;
      int *const left_block_end = left_it + max_left_swap_count;

      PRAGMA_UNROLL
      for (int *left_block_it = left_block_begin; left_block_it < left_block_end; ++left_block_it)
      {
        *left_swap_it = left_block_it;
        const int swap = *left_block_it >= pivot_key;
        left_swap_it += swap;
      }

      if (left_swap_it == left_swaps_begin)
      {
        left_it = left_block_end;
      }
    }

    int** right_swap_it = right_swaps_begin;
    while (right_it - left_it >= max_swap_count && right_swap_it == right_swaps_begin)
    {
      int* right_block_begin = right_it - max_right_swap_count + 1;
      int* const right_block_last = right_it;

      PRAGMA_UNROLL
      for (int* right_block_it = right_block_last; right_block_it >= right_block_begin; --right_block_it)
      {
        *right_swap_it = right_block_it;
        const int swap = *right_block_it < pivot_key;
        right_swap_it += swap;
      }

      if (right_swap_it == right_swaps_begin)
      {
        right_it = right_block_begin - 1;
      }
    }

    const ptrdiff_t left_swap_count = left_swap_it - left_swaps_begin;
    const ptrdiff_t right_swap_count = right_swap_it - right_swaps_begin;
    ptrdiff_t swap_count = left_swap_count < right_swap_count ? left_swap_count : right_swap_count;

    if (swap_count > 0)
    {
      left_swap_it = left_swaps_begin;
      right_swap_it = right_swaps_begin;
      int **const left_swap_last = left_swaps_begin + swap_count - 1;
      int **const right_swap_last = right_swaps_begin + swap_count - 1;

      while (left_swap_it <= left_swap_last)
      {
        int *const left_it_to_swap = *left_swap_it;
        int *const right_it_to_swap = *right_swap_it;

        const int temp_key = *left_it_to_swap;
        *left_it_to_swap = *right_it_to_swap;
        *right_it_to_swap = temp_key;

        left_swap_it++;
        right_swap_it++;
      }

      left_it = (*left_swap_last) + 1;
      right_it = (*right_swap_last) - 1;
    }
  }

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

  return (quick_partition_result_t){left_it + 1, right_it};
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_8(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 8, 8);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_16(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 16, 16);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_32(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 32, 32);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_64(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 64, 64);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_128(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 128, 128);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_256(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 256, 256);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_by_block_then_fit_1024(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  return quick_partition_swap_by_block_then_fit(keys_begin, keys_end, pivot_key_it, 512, 512);
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_swap_then_fit(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  const int pivot_key = *pivot_key_it;
  int* left_it = keys_begin;
  int* right_it = keys_end - 1;
  
  while (left_it < right_it)
  {
    while (*left_it < pivot_key)
    {
      left_it++;
    }    

    while (*right_it > pivot_key)
    {
      right_it--;
    }
    
    if (left_it < right_it)
    {
      const int left_key = *left_it;
      const int right_key = *right_it;
      *right_it = left_key;
      *left_it = right_key;

      if (left_key == right_key)
      {
        right_it--;
      }
    }
  }

  int* new_pivot_it = left_it;
  assert(*new_pivot_it == pivot_key);
  
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
  
  return (quick_partition_result_t){left_it + 1, right_it};  
}

__attribute__((always_inline))
WA_INLINE quick_partition_result_t quick_partition_three_ways(int* const keys_begin, int* const keys_end, int* const pivot_key_it)
{
  const int pivot_key = *pivot_key_it;
  int* low_it = keys_begin;
  int* mid_it = keys_begin;
  int* high_it = keys_end;
  
  while (mid_it < high_it)
  {
    const int mid_key = *mid_it;
    if (mid_key < pivot_key)
    {
      *mid_it = *low_it;
      *low_it = mid_key;
      low_it++;
      mid_it++;
    }
    else if (mid_key == pivot_key)
    {
      mid_it++;
    }
    else
    {
      high_it--;
      *mid_it = *high_it;
      *high_it = mid_key;
    }    
  }

  assert(*low_it == pivot_key);
  assert(*high_it > pivot_key);

  return (quick_partition_result_t){low_it, high_it};
}

typedef struct
{
  int* keys_begin;
  int* keys_end;
}
stack_element_t;

__attribute__((always_inline))
WA_INLINE void quick_sort(int* const base_keys, const int base_key_count, const quick_partition_t quick_partition, const quick_pivot_t quick_pivot)
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
    assert(keys_begin);
    assert(keys_end);

    const quick_partition_result_t result = quick_partition(keys_begin, keys_end, quick_pivot(keys_begin, keys_end));
    int* const left_dutch_end = result.left_dutch_end;
    int* const right_dutch_begin = result.right_dutch_begin;
    const int left_key_count = (int)(left_dutch_end - keys_begin);
    const int right_key_count = (int)(keys_end - right_dutch_begin);

    if (left_key_count > right_key_count)
    {
      if (left_key_count > 1)
      {
        assert(keys_begin);
        assert(left_dutch_end);
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
      
      if (right_key_count > 1)
      {
        assert(right_dutch_begin);
        assert(keys_end);
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }
    }
    else
    {
      if (right_key_count > 1)
      {
        assert(right_dutch_begin);
        assert(keys_end);
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }

      if (left_key_count > 1)
      {
        assert(keys_begin);
        assert(left_dutch_end);
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
    }
  }
}
