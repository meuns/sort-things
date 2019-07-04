#include "std_sort.h"

#include <algorithm>
#include <cstdlib>

void std_sort(int* keys, const int key_count)
{
  if (key_count > 1)
  {
    std::sort(&keys[0], &keys[key_count]);
  }
}

void std_stable_sort(int* keys, const int key_count)
{
  if (key_count > 1)
  {
    std::stable_sort(&keys[0], &keys[key_count]);
  }
}

static int std_qsort_compare(const void* left_key, const void* right_key)
{
  const int* left_key_int = static_cast<const int*>(left_key);
  const int* right_key_int = static_cast<const int*>(right_key);
  return *right_key_int - *left_key_int;
}

void std_qsort(int* keys, const int key_count)
{
  qsort(keys, static_cast<unsigned long>(key_count), sizeof(int), std_qsort_compare);
}

