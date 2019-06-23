#include "merge_sort.h"

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE int merge_compare_le(int left_key, int right_key)
{
  return left_key <= right_key;
}

__attribute__((always_inline))
WA_INLINE void merge_keys(int* restrict left_keys, const int left_key_count, int* restrict right_keys, const int right_key_count, int* restrict merged_keys, merge_compare_keys_t merge_compare)
{
  int left_index = 0;
  int left_key = left_keys[left_index];
  int right_index = 0;
  int right_key = right_keys[right_index];
  int merged_index = 0;
  
  while (left_index < left_key_count && right_index < right_key_count)
  {
    if (merge_compare(left_key, right_key))
    {
      merged_keys[merged_index] = left_key;
      left_index = left_index + 1;
      left_key = left_keys[left_index];
    }
    else
    {
      merged_keys[merged_index] = right_key;
      right_index = right_index + 1;
      right_key = right_keys[right_index];
    }
    
    merged_index = merged_index + 1;
  }
  
  while (left_index < left_key_count)
  {
    merged_keys[merged_index] = left_keys[left_index];
    left_index = left_index + 1;
    merged_index = merged_index + 1;
  }
  
  while (right_index < right_key_count)
  {
    merged_keys[merged_index] = right_keys[right_index];
    right_index = right_index + 1;
    merged_index = merged_index + 1;
  }
}

__attribute__((always_inline))
WA_INLINE void merge_sort(int* keys, const int key_count, int* temp_keys, merge_compare_keys_t merge_compare)
{
  int* input_keys = keys;
  int* output_keys = temp_keys;

  for (int left_key_count = 1; left_key_count <= key_count; left_key_count <<= 1)
  {
    int right_key_count = left_key_count;
    int merge_index = 0;
    int next_merge_index = merge_index + left_key_count + right_key_count;
    while (next_merge_index <= key_count)
    {
      merge_keys(&input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare);
      merge_index = next_merge_index;
      next_merge_index = merge_index + left_key_count + right_key_count;
    }
    
    if (merge_index + left_key_count < key_count)
    {
      right_key_count = key_count - (merge_index + left_key_count);
      merge_keys(&input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare);
    }
    else
    {
      for (int copy_index = merge_index; copy_index < key_count; ++copy_index)
      {
        output_keys[copy_index] = input_keys[copy_index];
      }
    }

    int* swap_keys = input_keys;
    input_keys = output_keys;
    output_keys = swap_keys;
  }

  if (input_keys == temp_keys)
  {
    for (int copy_index = 0; copy_index < key_count; ++copy_index)
    {
      keys[copy_index] = temp_keys[copy_index];
    }
  }
}
