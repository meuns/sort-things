#include "quick_sort.h"

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE char* quick_middle_pivot(char* const keys_begin, char* const keys_end, const quick_compare_t quick_compare __attribute__((unused)))
{
  return keys_begin + ((keys_end - keys_begin) >> 1);
}

__attribute__((always_inline))
WA_INLINE char* quick_median3_pivot(char* const keys_begin, char* const keys_end, const quick_compare_t quick_compare)
{
  char* low_key_it = keys_begin;
  char* mid_key_it = quick_middle_pivot(keys_begin, keys_end, quick_compare);
  char* high_key_it = keys_end - 1;

  if (quick_compare(high_key_it, mid_key_it) > 0) // *mid_key_it > *high_key_it
  {
    char* temp = mid_key_it;
    mid_key_it = high_key_it;
    high_key_it = temp;
  }

  if (quick_compare(high_key_it, low_key_it) > 0) // *low_key_it > *high_key_it
  {
    low_key_it = high_key_it;
  }

  if (quick_compare(mid_key_it, low_key_it) > 0) // *low_key_it > *mid_key_it
  {
    mid_key_it = low_key_it;
  }

  return mid_key_it;
}

__attribute__((always_inline))
WA_INLINE int quick_compare_default(const void* left_key, const void* right_key)
{
  const int* left_key_int = left_key;
  const int* right_key_int = right_key;
  return *right_key_int - *left_key_int;
}

typedef struct
{
  char* left_dutch_end;
  char* right_dutch_begin;
}
quick_partition_result_t;

__attribute__((always_inline))
static inline quick_partition_result_t quick_partition(char* const keys_begin, char* const keys_end, char* const pivot_key_it, const int key_size, const quick_compare_t quick_compare, const quick_copy_t quick_copy)
{
  char pivot_key[key_size];
  quick_copy(pivot_key, pivot_key_it);

  quick_copy(pivot_key_it, keys_begin);

  char* left_it = keys_begin + key_size;
  char* right_it = keys_end - key_size;
  
  while (right_it > left_it)
  {
    while (right_it > left_it && quick_compare(pivot_key, right_it) >= 0) // *right_it >= pivot_key
    {
      right_it -= key_size;
    }
    
    while (right_it > left_it && quick_compare(left_it, pivot_key) < 0) // *left_it < pivot_key
    {
      left_it += key_size;
    }

    if (right_it > left_it)
    {
      char right_key[key_size];
      quick_copy(right_key, right_it);
      quick_copy(right_it, left_it);
      quick_copy(left_it, right_it);

      right_it -= key_size;
      left_it += key_size;
    }
  }

  char* new_pivot_it = right_it;
  if (quick_compare(&pivot_key, right_it) >= 0) // *right_it >= pivot_key
  {
    new_pivot_it -= key_size;
  }

  quick_copy(keys_begin, new_pivot_it);
  quick_copy(new_pivot_it, &pivot_key);
  
  left_it = new_pivot_it;
  if (left_it > keys_begin)
  {
    left_it -= key_size;
    while (left_it > keys_begin && quick_compare(left_it, pivot_key) == 0) // *left_it == pivot_key
    {
      left_it -= key_size;
    }
  }

  right_it = new_pivot_it;
  if (right_it < keys_end)
  {
    right_it += key_size;
    while (right_it < keys_end && quick_compare(right_it, pivot_key) == 0) // *right_it == pivot_key
    {
      right_it += key_size;
    }
  }

  quick_partition_result_t result;
  result.left_dutch_end = left_it + 1;
  result.right_dutch_begin = right_it;
  return result;
}

typedef struct
{
  char* keys_begin;
  char* keys_end;
}
stack_element_t;

__attribute__((always_inline))
void quick_sort(void* const keys, const int key_count, const int key_size, const quick_pivot_t quick_pivot, const quick_compare_t quick_compare, const quick_copy_t quick_copy)
{
  if (key_count < 2)
  {
    return;
  }

  const int stack_size = 32;
  stack_element_t stack[stack_size];
  const stack_element_t* const stack_begin = stack;
  stack_element_t* stack_top_it = stack;

  char* const keys_char = keys;
  *stack_top_it = (stack_element_t){keys_char, keys_char + key_count * key_size};
  
  while (stack_top_it >= stack_begin)
  {
    const stack_element_t stack_element = *stack_top_it--;
    char* const keys_begin = stack_element.keys_begin;
    char* const keys_end = stack_element.keys_end;

    const quick_partition_result_t result = quick_partition(keys_begin, keys_end, quick_pivot(keys_begin, keys_end, quick_compare), key_size, quick_compare, quick_copy);
    char* const left_dutch_end = result.left_dutch_end;
    char* const right_dutch_begin = result.right_dutch_begin;
    const int left_keys_size = (int)(left_dutch_end - keys_begin);
    const int right_keys_size = (int)(keys_end - right_dutch_begin);

    if (left_keys_size > right_keys_size)
    {
      if (left_keys_size > 1)
      {
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
      
      if (right_keys_size > 1)
      {
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }
    }
    else
    {
      if (right_keys_size > 1)
      {
        *(++stack_top_it) = (stack_element_t){right_dutch_begin, keys_end};
      }

      if (left_keys_size > 1)
      {
        *(++stack_top_it) = (stack_element_t){keys_begin, left_dutch_end};
      }
    }
  }
}
