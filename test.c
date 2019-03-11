#include "test.h"

#include <stdlib.h>
#undef max
#undef min

void generate_keys(int* keys, const int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (int)(rand() % 256) - 128;
  }
}

static inline int min(int a, int b)
{
  return a < b ? a : b;
}

static inline int max(int a, int b)
{
  return a > b ? a : b;
}

int key_counts_are_equal(int* keys, int* sorted_keys, const int key_count)
{
  int min_key = keys[0];
  int max_key = keys[0];

  for (int key_index = 1; key_index < key_count; ++key_index)
  {
    min_key = min(min_key, keys[key_index]);
    max_key = max(max_key, keys[key_index]);
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    min_key = min(min_key, sorted_keys[key_index]);
    max_key = max(max_key, sorted_keys[key_index]);
  }

  const int histogram_size = max_key - min_key + 1;

  int* histogram = (int*)malloc(sizeof(int) * histogram_size);
  int* sorted_histogram = (int*)malloc(sizeof(int) * histogram_size);

  for (int entry_index = 0; entry_index < histogram_size; ++entry_index)
  {
    histogram[entry_index] = 0;
    sorted_histogram[entry_index] = 0;
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    histogram[keys[key_index] - min_key]++;
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    sorted_histogram[sorted_keys[key_index] - min_key]++;
  }

  int result = 1;
  for (int entry_index = 0; entry_index < histogram_size; ++entry_index)
  {
    if (histogram[entry_index] != sorted_histogram[entry_index])
    {
      result = 0;
      break;
    }
  }

  free(sorted_histogram);
  free(histogram);
  return result;
}

int keys_are_sorted(int* const keys, const int key_count)
{
  int key = keys[0];
  for (int key_index = 1; key_index < key_count; ++key_index)
  {
    const int next_key = keys[key_index];
    if (key > next_key)
    {
      return 0;
    }
    key = next_key;
  }
  
  return 1;
}
