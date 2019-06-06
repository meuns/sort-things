#include "debug.h"
#include "radix_sort.h"

int main()
{
  int keys[] = {
    -1100, 1200, 0, 200,
    500, -400, 1400, 100,
    900, 900, 600, 600,
    100, -200, 300, 1700
  };

  int key_count = sizeof(keys) / sizeof(keys[0]);

  int temp_keys[key_count];

  radix_sort_byte(keys, key_count, temp_keys, radix_always_sort_digit);

  debug_print_keys(keys, key_count);

  return 0;
}
