#include "debug.h"
#include "radix_sort.h"

int main()
{
  int keys[] = {
    -5232, 21388, 22806, 29215, 25163, -16756, 31307, 28118, -32338, 15149, -22178, -17887, -32341
  };

  int key_count = sizeof(keys) / sizeof(keys[0]);

  int temp_keys[key_count];

  debug_print_hex_keys(keys, key_count);

  radix_sort_byte(keys, key_count, temp_keys);

  debug_print_hex_keys(keys, key_count);

  return 0;
}
