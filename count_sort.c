#include "count_sort.h"

#include <limits.h>

void count_sort(unsigned char* const keys, unsigned char* sorted_keys, const int key_count)
{
  unsigned char histogram[UCHAR_MAX];
  
  for (int bin_index = 0; bin_index < UCHAR_MAX; ++bin_index)
  {
    histogram[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    histogram[keys[key_index]]++;
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
