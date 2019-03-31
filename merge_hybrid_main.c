#include "debug.h"
#include "merge_hybrid_sort.h"

#include <stdlib.h>

int main()
{
  const int key_count = 1024;
  int* keys = (int*)malloc(sizeof(int) * key_count);
  int* temp_keys = (int*)malloc(sizeof(int) * key_count);

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = key_index % 32;
  }
  
  merge_sort_hybrid(keys, key_count, temp_keys);
  
  debug_print_keys(keys, key_count);

  free(temp_keys);
  free(keys);

  return 0;
}
