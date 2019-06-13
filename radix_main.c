#include "debug.h"
#include "radix_sort.h"

int main()
{
  unsigned int keys[] = {
    0x00200010,
    0x00102010,
    0x80000000,
    0x80102010,
    0x00000000,
    0x80000002,
    0x80000050,
    0x00000000
  };

  int key_count = sizeof(keys) / sizeof(keys[0]);

  int temp_keys[key_count];

  radix_sort_byte((int*)keys, key_count, temp_keys);

  debug_print_keys((int*)keys, key_count);
  debug_print_hex_keys((int*)keys, key_count);

  return 0;
}
