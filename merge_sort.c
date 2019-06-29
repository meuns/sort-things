#include "merge_sort.h"

#include <string.h>

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE void merge_compare_and_copy_both(int* restrict merged_keys, int left_key, int right_key)
{
  if(left_key <= right_key)
  {
    merged_keys[0] = left_key;
    merged_keys[1] = right_key;
  }
  else
  {
    merged_keys[0] = right_key;
    merged_keys[1] = left_key;
  }
}

__attribute__((always_inline))
WA_INLINE void merge_keys(int* restrict left_keys, const int left_key_count, int* restrict right_keys, const int right_key_count, int* restrict merged_keys)
{
  const int* left_keys_end = left_keys + left_key_count;
  const int* right_keys_end = right_keys + right_key_count;

  int left_key = *left_keys;
  int right_key = *right_keys;
  left_keys++;
  right_keys++;
  
  while (left_keys < left_keys_end && right_keys < right_keys_end)
  {
    if (left_key <= right_key)
    {
      *merged_keys = left_key;
      merged_keys++;
      
      left_key = *left_keys;
      left_keys++;
    }
    else
    {
      *merged_keys = right_key;
      merged_keys++;
      
      right_key = *right_keys;
      right_keys++;
    }
  }

  if (left_keys < left_keys_end)
  {
    while (left_keys < left_keys_end && left_key <= right_key)
    {
      *merged_keys = left_key;
      merged_keys++;
      
      left_key = *left_keys;
      left_keys++;
    }

    merge_compare_and_copy_both(merged_keys, left_key, right_key);
    merged_keys += 2;

    // We use memcpy because clang isn't able to replace a more generic copy loop by itself
    memcpy(merged_keys, left_keys, (size_t)(left_keys_end - left_keys) * sizeof(int));
  }
  else if (right_keys < right_keys_end)
  {
    while (right_keys < right_keys_end && left_key > right_key)
    {      
      *merged_keys = right_key;
      merged_keys++;
      
      right_key = *right_keys;
      right_keys++;
    }

    merge_compare_and_copy_both(merged_keys, left_key, right_key);
    merged_keys += 2;

    // We use memcpy because clang isn't able to replace a more generic copy loop by itself
    memcpy(merged_keys, right_keys, (size_t)(right_keys_end - right_keys) * sizeof(int));
  }
  else
  {
    merge_compare_and_copy_both(merged_keys, left_key, right_key);
  }
}

__attribute__((always_inline))
WA_INLINE void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  int* input_keys = keys;
  int* output_keys = temp_keys;

  for (int left_key_count = 1; left_key_count <= key_count; left_key_count <<= 1)
  {
    int right_key_count = left_key_count;

    const int* input_keys_end = input_keys + key_count;
    int* input_cursor = input_keys;
    int* next_input_cursor = input_cursor + left_key_count + right_key_count;
    int* output_cursor = output_keys;

    while (next_input_cursor <= input_keys_end)
    {
      merge_keys(input_cursor, left_key_count, input_cursor + left_key_count, right_key_count, output_cursor);
      input_cursor = next_input_cursor;
      output_cursor += left_key_count + right_key_count;
      next_input_cursor += left_key_count + right_key_count;
    }
    
    if (input_cursor + left_key_count < input_keys_end)
    {
      right_key_count = (int)(input_keys_end - (input_cursor + left_key_count));
      merge_keys(input_cursor, left_key_count, input_cursor + left_key_count, right_key_count, output_cursor);
    }
    else
    {
      memcpy(output_cursor, input_cursor, (size_t)(input_keys_end - input_cursor) * sizeof(int));
    }

    int* swap_keys = input_keys;
    input_keys = output_keys;
    output_keys = swap_keys;
  }

  if (input_keys == temp_keys)
  {
    memcpy(keys, temp_keys, (size_t)key_count * sizeof(int));
  }
}
