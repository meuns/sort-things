#include "std_sort.h"

#include <algorithm>

void std_sort(int* keys, const int key_count)
{
  if (key_count > 1)
  {
    std::sort(&keys[0], &keys[key_count]);
  }
}
