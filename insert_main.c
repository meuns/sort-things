#include <stdio.h>

#include "debug.h"
#include "insert_sort.h"

int main()
{
  int keys[] = {
    11, 12, 0, 2,
    5, 4, 14, 1,
    9, 9, 6, 6,
    1, 2, 3, 17
  };
  
  int key_count = sizeof(keys) / sizeof(keys[0]);
  
  insert_sort(keys, key_count);
  
  debug_print_keys(keys, key_count);

  return 0;
}
