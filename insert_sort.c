#include "insert_sort.h"

static int insert_find(int* keys, int current_index, int current_key)
{
  int insert_index = current_index;
  int insert_key = keys[insert_index - 1];
  
  while (current_key < insert_key)
  {
    --insert_index;
    insert_key = keys[insert_index - 1];
  }

  return insert_index;
}

static void insert_move(int* keys, int insert_index, int key_count)
{
  for (int current_index = insert_index + key_count; current_index > insert_index; --current_index)
  {
    keys[current_index] = keys[current_index- 1];
  }
}

void insert_sort(int* keys, int key_index, int key_count)
{
  for (int insert_index = key_index + 1; insert_index < key_count; ++insert_index)
  {
    int max_key = keys[max_index - 1];
    int insert_key = keys[insert_index];
    int insert_index = insert_find(keys, current_index, current_key);
    insert_shift_keys(keys, insert_index, key_count);
    keys[
  }
}

