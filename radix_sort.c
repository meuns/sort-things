#include "count_sort.h"

#include <limits.h>

unsigned char radix_key_byte(const int key, const int byte_index)
{
  const int mask = 0xFF;
  const int bit_shift = byte_index << 3;
  return (key & (mask << bit_shift)) >> bit_shift;
}

void radix_sort_byte(int* input_keys, int* output_keys, const int key_count, const int byte_index)
{
  unsigned char histogram[UCHAR_MAX];
  
  for (int bin_index = 0; bin_index < UCHAR_MAX; ++bin_index)
  {
    histogram[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const unsigned char key_byte = radix_key_byte(input_keys[key_index], byte_index);
    histogram[key_byte]++;
  }
  
  for (int bin_index = 1; bin_index <= UCHAR_MAX; ++bin_index)
  {
    histogram[bin_index] += histogram[bin_index - 1];
  }
  
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const unsigned char key_byte = radix_key_byte(key, byte_index);
    output_keys[--histogram[key_byte]] = key;
  }
}

void radix_sort(int* keys, const int key_count, int* temp_keys)
{
  radix_sort_byte(keys, temp_keys, key_count, 0);
  radix_sort_byte(temp_keys, keys, key_count, 1);
  radix_sort_byte(keys, temp_keys, key_count, 2);
  radix_sort_byte(temp_keys, keys, key_count, 3);
}
