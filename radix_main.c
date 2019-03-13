#include <stdio.h>
#include "radix_sort.h"

int main()
{
  int keys[] = {
    1100, 1200, 0, 200,
    500, 400, 1400, 100,
    900, 900, 600, 600,
    100, 200, 300, 1700
  };

  int key_count = sizeof(keys) / sizeof(keys[0]);

  int temp_keys[key_count];

  radix_sort(keys, key_count, temp_keys);

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    printf("%d ", keys[key_index]);
  }

  printf("\n");

  return 0;
}
