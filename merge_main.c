#include "debug.h"
#include "merge_sort.h"

int main()
{
  int keys[] = {
    11, 12, 0, 2,
    5, 4, 14, 1,
    9, 9, 6, 6,
    1, 2, 3, 17
  };
  
  int key_count = sizeof(keys) / sizeof(keys[0]);
  
  int temp_keys[key_count];
  
  merge_sort(keys, key_count, temp_keys, merge_compare_default);
  
  debug_print_keys(keys, key_count);

  return 0;
}
