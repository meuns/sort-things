#include "insert_sort.h"

__attribute__((always_inline))
static inline int insert_find_index(int* const keys, int insert_index, const int insert_key)
{
  int compare_key = keys[insert_index - 1];

  while (insert_key < compare_key && insert_index > 0)
  {
    keys[insert_index] = compare_key;
    insert_index = insert_index - 1;
    compare_key = keys[insert_index - 1];
  }

  return insert_index;
}

__attribute__((noinline))
void insert_sort(int* keys, const int key_count)
{
  for (int current_index = 1; current_index < key_count; ++current_index)
  {
    const int insert_key = keys[current_index];
    const int insert_index = insert_find_index(keys, current_index, insert_key);
    keys[insert_index] = insert_key;
  }
}
