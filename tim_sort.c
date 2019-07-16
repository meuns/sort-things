#include "tim_sort.h"

#include "merge_sort.h"

#include <stddef.h>

#if defined(WA_LINKING_INLINE_FUNCTION)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE int* tim_find_run(int* const run_begin, const int* const keys_end)
{
  int* run_end = run_begin + 1;
  while (run_end < keys_end && *run_end > )
  {

  }
}

// int* const left_run_begin, int* const left_run_end, int* const right_run_begin, int* const right_run_end, int* const merged_run_begin

__attribute__((always_inline))
WA_INLINE tim_stack_element_t* tim_merge_collapse(tim_stack_element_t* stack_top_it, const tim_stack_element_t* const stack_begin)
{
  while (stack_top_it >= stack_begin)
  {
    const ptrdiff_t stack_size = stack_top_it - stack_begin + 1;
    if (
      (stack_size > 2 && stack_top_it[2].run_length <= stack_top_it[1].run_length + stack_top_it[0].run_length) ||
      (stack_size > 3 && stack_top_it[3].run_length <= stack_top_it[2].run_length + stack_top_it[1].run_length)
    )
    {
      if (stack_top_it[3].run_length < stack_top_it[1].run_length)
      {

      }
      else
      {

      }
    }
    else if (stack_top_it[2].run_length <= stack_top_it[1].run_length)
    {

    }
    else
    {
      break;
    }
  }
}

typedef struct
{
  int* run_begin;
  ptrdiff_t run_length;
}
tim_stack_element_t;

__attribute__((always_inline))
WA_INLINE void tim_sort(int* keys, const int key_count, int* temp_keys)
{
  const int stack_size = 32;
  tim_stack_element_t stack[stack_size];
  const tim_stack_element_t* const stack_begin = stack;
  tim_stack_element_t* stack_top_it = stack;

  int* const keys_begin = keys;
  const int* const keys_end = keys + key_count;

  *stack_top_it = (tim_stack_element_t){keys_begin, tim_find_run(keys_begin, keys_end)};

  while (stack_top_it >= stack_begin)
  {

  }
}
