#include "merge_sort.h"

#include <string.h>

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

__attribute__((always_inline))
WA_INLINE int merge_compare_default(const void* left_key, const void* right_key)
{
  const int* left_key_int = (const int*)left_key;
  const int* right_key_int = (const int*)right_key;
  return *left_key_int <= *right_key_int;
}

__attribute__((always_inline))
WA_INLINE void merge_copy_default(void* to_key, const void* from_key)
{
  int* to_key_int = (int*)to_key;
  const int* from_key_int = (const int*)from_key;
  *to_key_int = *from_key_int;
}

__attribute__((always_inline))
WA_INLINE void merge_keys(const int key_size, void* restrict left_keys, const int left_key_count, void* restrict right_keys, const int right_key_count, void* restrict merged_keys, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy)
{
  char* left_keys_char = (char*)left_keys;
  char* right_keys_char = (char*)right_keys;
  char* merged_keys_char = (char*)merged_keys;
  const int left_keys_size = left_key_count * key_size;
  const int right_keys_size = right_key_count * key_size;

  int left_offset = 0;
  int right_offset = 0;
  int merged_offset = 0;

  char left_key[key_size];
  char right_key[key_size];
  merge_copy(&left_key, &left_keys_char[left_offset]);
  merge_copy(&right_key, &right_keys_char[right_offset]);
  
  while (left_offset < left_keys_size && right_offset < right_keys_size)
  {
    if (merge_compare(&left_key, &right_key))
    {
      merge_copy(&merged_keys_char[merged_offset], &left_key);
      left_offset += key_size;
      merge_copy(&left_key, &left_keys_char[left_offset]);
    }
    else
    {
      merge_copy(&merged_keys_char[merged_offset], &right_key);
      right_offset += key_size;
      merge_copy(&right_key, &right_keys_char[right_offset]);
    }
    
    merged_offset += key_size;
  }
  
  // We use memcpy because clang isn't able to replace a more generic copy loop by itself
  memcpy(&merged_keys_char[merged_offset], &left_keys_char[left_offset], (size_t)(left_keys_size - left_offset));

  // We use memcpy because clang isn't able to replace a more generic copy loop by itself
  memcpy(&merged_keys_char[merged_offset], &right_keys_char[right_offset], (size_t)(right_keys_size - right_offset));
}

__attribute__((always_inline))
WA_INLINE void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy)
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
      merge_keys(4, &input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare, merge_copy);
      merge_index = next_merge_index;
      next_merge_index = merge_index + left_key_count + right_key_count;
    }
    
    if (merge_index + left_key_count < key_count)
    {
      right_key_count = key_count - (merge_index + left_key_count);
      merge_keys(4, &input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare, merge_copy);
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
