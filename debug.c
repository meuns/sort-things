#include "debug.h"

#include <stdio.h>

void debug_print_keys(int* const keys, const int key_count)
{
  printf("{");

  const int last_key_index = key_count - 1;
  for (int key_index = 0; key_index < last_key_index; ++key_index)
  {
    printf("%d, ", keys[key_index]);
  }

  printf("%d}\n", keys[last_key_index]);
}
