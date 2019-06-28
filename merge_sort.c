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
WA_INLINE void merge_compare_and_copy_both(int key_size, char* merged_keys_char, char* left_key, char* right_key, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy)
{
  if(merge_compare(left_key, right_key))
  {
    merge_copy(&merged_keys_char[0], left_key);
    merge_copy(&merged_keys_char[key_size], right_key);
  }
  else
  {
    merge_copy(&merged_keys_char[0], right_key);
    merge_copy(&merged_keys_char[key_size], left_key);
  }
}

__attribute__((always_inline))
WA_INLINE void merge_keys(const int key_size, void* restrict left_keys, const int left_keys_size, void* restrict right_keys, const int right_keys_size, void* restrict merged_keys, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy)
{
  char* left_keys_char = (char*)left_keys;
  char* right_keys_char = (char*)right_keys;
  char* merged_keys_char = (char*)merged_keys;
  const char* left_keys_char_end = left_keys_char + left_keys_size;
  const char* right_keys_char_end = right_keys_char + right_keys_size;

  char left_key[key_size];
  char right_key[key_size];
  merge_copy(left_key, left_keys_char);
  left_keys_char += key_size;
  merge_copy(right_key, right_keys_char);
  right_keys_char += key_size;
  
  while (left_keys_char < left_keys_char_end && right_keys_char < right_keys_char_end)
  {
    if (merge_compare(left_key, right_key))
    {
      merge_copy(merged_keys_char, left_key);
      merged_keys_char += key_size;
      
      merge_copy(left_key, left_keys_char);
      left_keys_char += key_size;
    }
    else
    {
      merge_copy(merged_keys_char, &right_key);
      merged_keys_char += key_size;
      
      merge_copy(&right_key, right_keys_char);
      right_keys_char += key_size;
    }
  }

  if (left_keys_char < left_keys_char_end)
  {
    while (left_keys_char < left_keys_char_end && merge_compare(left_key, right_key))
    {
      merge_copy(merged_keys_char, left_key);
      merged_keys_char += key_size;
      
      merge_copy(left_key, left_keys_char);
      left_keys_char += key_size;
    }

    merge_compare_and_copy_both(key_size, merged_keys_char, left_key, right_key, merge_compare, merge_copy);
    merged_keys_char += 2 * key_size;

    // We use memcpy because clang isn't able to replace a more generic copy loop by itself
    memcpy(merged_keys_char, left_keys_char, (size_t)(left_keys_char_end - left_keys_char));
  }
  else if (right_keys_char < right_keys_char_end)
  {
    while (right_keys_char < right_keys_char_end && !merge_compare(&left_key, &right_key))
    {      
      merge_copy(merged_keys_char, right_key);
      merged_keys_char += key_size;
      
      merge_copy(right_key, right_keys_char);
      right_keys_char += key_size;
    }

    merge_compare_and_copy_both(key_size, merged_keys_char, left_key, right_key, merge_compare, merge_copy);
    merged_keys_char += 2 * key_size;

    // We use memcpy because clang isn't able to replace a more generic copy loop by itself
    memcpy(merged_keys_char, right_keys_char, (size_t)(right_keys_char_end - right_keys_char));
  }
  else
  {
    merge_compare_and_copy_both(key_size, merged_keys_char, left_key, right_key, merge_compare, merge_copy);
  }
}

__attribute__((always_inline))
WA_INLINE void merge_sort(void* restrict keys, const int key_count, const int key_size, void* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy)
{
  char* input_keys = keys;
  char* output_keys = temp_keys;
  
  const int keys_size = key_count * key_size;

  for (int left_keys_size = key_size; left_keys_size <= keys_size; left_keys_size <<= 1)
  {
    int right_keys_size = left_keys_size;

    const char* input_keys_end = input_keys + keys_size;
    char* input_cursor = input_keys;
    char* next_input_cursor = input_cursor + left_keys_size + right_keys_size;
    char* output_cursor = output_keys;

    while (next_input_cursor <= input_keys_end)
    {
      merge_keys(key_size, input_cursor, left_keys_size, input_cursor + left_keys_size, right_keys_size, output_cursor, merge_compare, merge_copy);
      input_cursor = next_input_cursor;
      output_cursor += left_keys_size + right_keys_size;
      next_input_cursor += left_keys_size + right_keys_size;
    }
    
    if (input_cursor + left_keys_size < input_keys_end)
    {
      right_keys_size = (int)(input_keys_end - (input_cursor + left_keys_size));
      merge_keys(key_size, input_cursor, left_keys_size, input_cursor + left_keys_size, right_keys_size, output_cursor, merge_compare, merge_copy);
    }
    else
    {
      memcpy(output_cursor, input_cursor, (size_t)(input_keys_end - input_cursor));
    }

    char* swap_keys = input_keys;
    input_keys = output_keys;
    output_keys = swap_keys;
  }

  if (input_keys == temp_keys)
  {
    memcpy(keys, temp_keys, (size_t)keys_size);
  }
}
