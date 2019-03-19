#include "count_sort.h"

#include <limits.h>

__attribute__((noinline))
void count_sort(signed char* const keys, const int key_count, signed char* sorted_keys)
{
  const int histogram_size = UCHAR_MAX + 1;
  int histogram[histogram_size];
  
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const unsigned char histogram_key = (unsigned char)(keys[key_index] ^ 0x80);
    histogram[histogram_key]++;
  }

  for (int bin_index = 1; bin_index < histogram_size; ++bin_index)
  {
    histogram[bin_index] += histogram[bin_index - 1];
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const char key = keys[key_index];
    const unsigned char histogram_key = (unsigned char)(key ^ 0x80);
    sorted_keys[--histogram[histogram_key]] = key;
  }
}

