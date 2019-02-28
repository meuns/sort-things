#include "insert_sort.h"

__attribute__((always_inline))
static int insert_find_index(int* keys, int insert_index, int insert_key)
{
  int compare_index = insert_index - 1;
  int compare_key = keys[compare_index];
  
  while (insert_key < compare_key && compare_index >= 0)
  {
    compare_index = compare_index - 1;
    compare_key = keys[compare_index];
  }
  
  insert_index = compare_index + 1;

  return insert_index;
}

__attribute__((always_inline))
static void insert_shift_keys(int* keys, int insert_index, int current_index)
{
  int to_index = current_index;
  int from_index = current_index - 1;
  
  while (to_index > insert_index)
  {
    keys[to_index] = keys[from_index];
    to_index = from_index;
    from_index = from_index - 1;
  }
}

void insert_sort(int* keys, int key_count)
{
  for (int current_index = 1; current_index < key_count; ++current_index)
  {
    const int insert_key = keys[current_index];
    const int insert_index = insert_find_index(keys, current_index, insert_key);    
    insert_shift_keys(keys, insert_index, current_index);
    keys[insert_index] = insert_key;
  }
}
