#include "quick_sort.h"
#include <stdio.h>

__attribute__((always_inline))
static inline int quick_pivot_index(int* keys, const int key_count)
{
  return key_count >> 1;
}

//for (int key_index = 1; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");

__attribute__((always_inline))
static inline int quick_partition(int* keys, const int key_count, const int pivot_index, const int pivot_key)
{
  //printf("quick_partition "); for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");  
  //printf("quick_partition with %d : ", pivot_key); printf("\n");  
  //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");
  
  keys[pivot_index] = keys[0];
  keys[0] = -666;
  
  int left_index = 1;
  int left_key = keys[left_index];
  
  int right_index = key_count - 1;
  int right_key = keys[right_index];
  
  //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");
  
  while (right_key >= pivot_key)
  {
    //printf("r\n");
    right_index = right_index - 1;
    right_key = keys[right_index];
  }
  
  while (left_key < pivot_key)
  {
    //printf("l\n");
    keys[left_index - 1] = left_key;
    left_index = left_index + 1;
    left_key = keys[left_index];      
  }
  
  while (left_index < right_index)
  {
    //printf("s %d %d\n", left_key, right_key);
    keys[right_index] = left_key;
    keys[left_index] = -666;
    keys[left_index - 1] = right_key;
    
    //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");
       
    right_index = right_index - 1;
    right_key = keys[right_index];
    left_index = left_index + 1;
    left_key = keys[left_index];
  
    while (right_key >= pivot_key)
    {
      //printf("r\n");
      right_index = right_index - 1;
      right_key = keys[right_index];
    }
    
    while (left_key < pivot_key)
    {
      //printf("l\n");
      keys[left_index - 1] = left_key;
      left_index = left_index + 1;
      left_key = keys[left_index];      
    }
  }
  
  keys[right_index] = pivot_key;
  
  //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d ", keys[key_index]); } printf("\n");
  
  return right_index;
}

void quick_sort(int* keys, const int key_count)
{
  if (key_count < 2)
  {
    return;
  }
  
  int pivot_index = quick_pivot_index(keys, key_count);
  int pivot_key = keys[pivot_index];
  
  //printf ("quick_sort %d %d\n", key_index, key_count);
  
  pivot_index = quick_partition(keys, key_count, pivot_index, pivot_key);
  
  quick_sort(keys, pivot_index);
  quick_sort(keys + pivot_index + 1, key_count - pivot_index - 1);
  
  //quick_sort(keys, pivot_index);
  //quick_sort(keys + pivot_index + 1, key_count - pivot_index - 1);
}
