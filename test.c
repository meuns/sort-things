#include "test.h"

#include <stdlib.h>
#undef max
#undef min

#define KEY_TYPE int
#define CONCAT_SUFFIX(name) name##_int
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE

void generate_keys_int(int* keys, const int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = rand();
  }
}

#define KEY_TYPE signed char
#define CONCAT_SUFFIX(name) name##_char
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE

void generate_keys_char(signed char* keys, const int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (signed char)(rand() % 256) - 128;
  }
}
