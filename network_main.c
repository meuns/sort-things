#include "debug.h"
#include "network_sort.h"

#include <stdlib.h>

int main()
{
  const int key_count = rand() % 16;
  int* keys = (int*)malloc(sizeof(int) * (unsigned)key_count);

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = key_index % 4;
  }
  
  network_sort(keys, key_count);
  
  debug_print_keys(keys, key_count);

  free(keys);

  return 0;
}
