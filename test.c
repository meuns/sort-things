#include "test.h"

#include <stdlib.h>

void generate_keys(int* keys, const int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (int)(rand() % 256) - 128;
  }
}

int keys_are_sorted(int* const keys, const int key_count)
{
  int key = keys[0];
  for (int key_index = 1; key_index < key_count; ++key_index)
  {
    const int next_key = keys[key_index];
    if (key > next_key)
    {
      return 0;
    }
    key = next_key;
  }
  
  return 1;
}
