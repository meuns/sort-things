#include "merge_sort.h"

static inline void merge_keys(int* left_keys, const int left_key_count, int* right_keys, const int right_key_count, int* merged_keys)
{
  int left_index = 0;
  int left_key = left_keys[left_index];
  int right_index = 0;
  int right_key = right_keys[right_index];
  int merged_index = 0;
  
  while (left_index < left_key_count && right_index < right_key_count)
  {
    if (left_key <= right_key)
    {
      merged_keys[merged_index] = left_key;
      
      left_key = left_keys[left_index];
      left_index = left_index + 1;
    }
    else
    {
      merged_keys[merged_index] = right_key;
      
      right_key = right_keys[right_index];
      right_index = right_index + 1;
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
  
  const int merged_key_count = merged_index;
  for (int copy_index = 0; copy_index < merged_key_count; ++copy_index)
  {
    left_keys[copy_index] = merged_keys[copy_index];
  }
}

void merge_sort(int* keys, int key_count, int* temp_keys)
{
  for (int merged_key_count = 2; merged_key_count < key_count; merged_key_count <<= 1)
  {
    int left_key_count = merged_key_count >> 1;
    int right_key_count = left_key_count;
    
    int merge_index = 0;
    while (merge_index < key_count)
    {
      merge_keys(&keys[merge_index], left_key_count, &keys[merge_index + left_key_count], right_key_count, temp_keys);
      merge_index = merge_index + merged_key_count;
    }
    
    
  }
}
