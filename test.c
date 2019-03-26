#include "test.h"

#include <stdlib.h>
#undef max
#undef min

static inline long long int min(long long int a, long long int b)
{
  return a < b ? a : b;
}

static inline long long int max(long long int a, long long int b)
{
  return a > b ? a : b;
}

#define KEY_TYPE int
#define CONCAT_SUFFIX(name) name##_int
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE

void test_generate_keys_int(int* keys, const long long int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (rand() % 65536) - 32768;
  }
}

#define KEY_TYPE signed char
#define CONCAT_SUFFIX(name) name##_char
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE

void test_generate_keys_char(signed char* keys, const long long int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (signed char)((rand() % 256) - 128);
  }
}
