#include "count_sort.h"

#include <limits.h>

unsigned char radix_key_byte(int key, const int byte_index)
{
  return (key & (0xFF << (byte_index << 3))) >> (byte_index << 3);
}

/*
void radix_sort_byte(int* input_keys, int* output_keys, const int key_count, const int byte_index)
{
  unsigned char histogram[UCHAR_MAX];
  
  for (int bin_index = 0; bin_index < UCHAR_MAX; ++bin_index)
  {
    histogram[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    unsigned char key_byte = keys[key_index];
    histogram[key_byte]++;
  }
  
  for (int bin_index = 1; bin_index < UCHAR_MAX; ++bin_index)
  {
    histogram[bin_index] += histogram[bin_index - 1];
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    unsigned char key = keys[key_index];
    sorted_keys[--histogram[key]] = key;
  }
}

void radix_sort(int* keys, int* temp_keys, const int key_count)
{
  radix_sort_byte(keys, temp_keys, key_count, 0);
  radix_sort_byte(temp_keys, keys, key_count, 1);
  radix_sort_byte(keys, temp_keys, key_count, 2);
  radix_sort_byte(temp_keys, keys, key_count, 3);
}
*/

