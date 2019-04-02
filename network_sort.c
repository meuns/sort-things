#include "network_sort.h"

#undef max
#undef min

__attribute__((always_inline))
inline int min(const int a, const int b)
{
  return a < b ? a : b;
}

__attribute__((always_inline))
inline int max(const int a, const int b)
{
  return a > b ? a : b;
}

__attribute__((always_inline))
inline void network_swap(int* keys, const int key_index0, const int key_index1)
{
  const int key0 = keys[key_index0];
  const int key1 = keys[key_index1];
  const int min_key = min(key0, key1);
  const int max_key = max(key0, key1);
  keys[key_index0] = min_key;
  keys[key_index1] = max_key;
}

typedef void (*network_sort_t)(int* keys);

__attribute__((always_inline))
inline void network_sort_02(int* keys)
{
  network_swap(keys, 0, 1);
}

__attribute__((always_inline))
inline void network_sort_03(int* keys)
{
  network_swap(keys, 1, 2);
  network_swap(keys, 0, 2);
  network_swap(keys, 0, 1);
}

__attribute__((always_inline))
inline void network_sort_04(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 0, 2);
  network_swap(keys, 1, 3);
  network_swap(keys, 1, 2);
}

__attribute__((always_inline))
inline void network_sort_05(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 3, 4);
  network_swap(keys, 2, 4);
  network_swap(keys, 2, 3);
  network_swap(keys, 0, 3);
  network_swap(keys, 0, 2);
  network_swap(keys, 1, 4);
  network_swap(keys, 1, 3);
  network_swap(keys, 1, 2);
}

__attribute__((always_inline))
inline void network_sort_06(int* keys)
{
  // Resorted by dependencies
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 0, 2);
  network_swap(keys, 1, 3);
  network_swap(keys, 1, 2);
  network_swap(keys, 0, 4);
  network_swap(keys, 1, 5);
  network_swap(keys, 1, 4);  
  network_swap(keys, 2, 4);
  network_swap(keys, 3, 5);
  network_swap(keys, 3, 4);
}

__attribute__((always_inline))
inline void network_sort_07(int* keys)
{
  // Resorted by dependencies
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);  
  network_swap(keys, 0, 2);
  network_swap(keys, 1, 3);
  network_swap(keys, 4, 6);  
  network_swap(keys, 1, 2);
  network_swap(keys, 5, 6);
  network_swap(keys, 0, 4);  
  network_swap(keys, 1, 5);
  network_swap(keys, 1, 4);
  network_swap(keys, 2, 6);
  network_swap(keys, 3, 6);
  network_swap(keys, 2, 4);
  network_swap(keys, 3, 5);
  network_swap(keys, 3, 4);
}

__attribute__((always_inline))
inline void network_sort_08(int* keys)
{
  // Resorted by dependencies
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 0, 2);
  network_swap(keys, 1, 3);
  network_swap(keys, 4, 6);
  network_swap(keys, 5, 7);
  network_swap(keys, 1, 2);
  network_swap(keys, 5, 6);
  network_swap(keys, 0, 4);
  network_swap(keys, 3, 7);
  network_swap(keys, 1, 5);
  network_swap(keys, 1, 4);
  network_swap(keys, 2, 6);
  network_swap(keys, 3, 6);
  network_swap(keys, 2, 4);
  network_swap(keys, 3, 5);
  network_swap(keys, 3, 4);
}

__attribute__((always_inline))
inline void network_sort_09(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 3, 4);
  network_swap(keys, 6, 7);
  network_swap(keys, 1, 2);
  network_swap(keys, 4, 5);
  network_swap(keys, 7, 8);
  network_swap(keys, 0, 1);
  network_swap(keys, 3, 4);
  network_swap(keys, 6, 7);
  network_swap(keys, 0, 3);
  network_swap(keys, 3, 6);
  network_swap(keys, 0, 3);
  network_swap(keys, 1, 4);
  network_swap(keys, 4, 7);
  network_swap(keys, 1, 4);
  network_swap(keys, 2, 5);
  network_swap(keys, 5, 8);
  network_swap(keys, 2, 5);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 2, 6);
  network_swap(keys, 4, 6);
  network_swap(keys, 2, 4);
  network_swap(keys, 2, 3);
  network_swap(keys, 5, 6);
}

__attribute__((always_inline))
inline void network_sort_10(int* keys)
{
  network_swap(keys, 4, 9);
  network_swap(keys, 3, 8);
  network_swap(keys, 2, 7);
  network_swap(keys, 1, 6);
  network_swap(keys, 0, 5);
  network_swap(keys, 1, 4);
  network_swap(keys, 6, 9);
  network_swap(keys, 0, 3);
  network_swap(keys, 5, 8);
  network_swap(keys, 0, 2);
  network_swap(keys, 3, 6);
  network_swap(keys, 7, 9);
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 4);
  network_swap(keys, 5, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 1, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 7, 8);
  network_swap(keys, 3, 5);
  network_swap(keys, 2, 5);
  network_swap(keys, 6, 8);
  network_swap(keys, 1, 3);
  network_swap(keys, 4, 7);
  network_swap(keys, 2, 3);
  network_swap(keys, 6, 7);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 4, 5);
}

__attribute__((always_inline))
inline void network_sort_11(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 0, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 10);
  network_swap(keys, 1, 2);
  network_swap(keys, 5, 6);
  network_swap(keys, 9, 10);
  network_swap(keys, 1, 5);
  network_swap(keys, 6, 10);
  network_swap(keys, 5, 9);
  network_swap(keys, 2, 6);
  network_swap(keys, 1, 5);
  network_swap(keys, 6, 10);
  network_swap(keys, 0, 4);
  network_swap(keys, 3, 7);
  network_swap(keys, 4, 8);
  network_swap(keys, 0, 4);
  network_swap(keys, 1, 4);
  network_swap(keys, 7, 10);
  network_swap(keys, 3, 8);
  network_swap(keys, 2, 3);
  network_swap(keys, 8, 9);
  network_swap(keys, 2, 4);
  network_swap(keys, 7, 9);
  network_swap(keys, 3, 5);
  network_swap(keys, 6, 8);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 7, 8);
}

__attribute__((always_inline))
inline void network_sort_12(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 10, 11);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 9, 11);
  network_swap(keys, 0, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 10);
  network_swap(keys, 1, 2);
  network_swap(keys, 5, 6);
  network_swap(keys, 9, 10);
  network_swap(keys, 1, 5);
  network_swap(keys, 6, 10);
  network_swap(keys, 5, 9);
  network_swap(keys, 2, 6);
  network_swap(keys, 1, 5);
  network_swap(keys, 6, 10);
  network_swap(keys, 0, 4);
  network_swap(keys, 7, 11);
  network_swap(keys, 3, 7);
  network_swap(keys, 4, 8);
  network_swap(keys, 0, 4);
  network_swap(keys, 7, 11);
  network_swap(keys, 1, 4);
  network_swap(keys, 7, 10);
  network_swap(keys, 3, 8);
  network_swap(keys, 2, 3);
  network_swap(keys, 8, 9);
  network_swap(keys, 2, 4);
  network_swap(keys, 7, 9);
  network_swap(keys, 3, 5);
  network_swap(keys, 6, 8);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 7, 8);
}

__attribute__((always_inline))
inline void network_sort_13(int* keys)
{
  network_swap(keys, 1, 7);
  network_swap(keys, 9, 11);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 8);
  network_swap(keys, 0, 12);
  network_swap(keys, 2, 6);
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 11);
  network_swap(keys, 7, 12);
  network_swap(keys, 5, 9);
  network_swap(keys, 0, 2);
  network_swap(keys, 3, 7);
  network_swap(keys, 10, 11);
  network_swap(keys, 1, 4);
  network_swap(keys, 6, 12);
  network_swap(keys, 7, 8);
  network_swap(keys, 11, 12);
  network_swap(keys, 4, 9);
  network_swap(keys, 6, 10);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 8, 9);
  network_swap(keys, 10, 11);
  network_swap(keys, 1, 7);
  network_swap(keys, 2, 6);
  network_swap(keys, 9, 11);
  network_swap(keys, 1, 3);
  network_swap(keys, 4, 7);
  network_swap(keys, 8, 10);
  network_swap(keys, 0, 5);
  network_swap(keys, 2, 5);
  network_swap(keys, 6, 8);
  network_swap(keys, 9, 10);
  network_swap(keys, 1, 2);
  network_swap(keys, 3, 5);
  network_swap(keys, 7, 8);
  network_swap(keys, 4, 6);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
}

__attribute__((always_inline))
inline void network_sort_14(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 10, 11);
  network_swap(keys, 12, 13);
  network_swap(keys, 0, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 10);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 9, 11);
  network_swap(keys, 0, 4);
  network_swap(keys, 8, 12);
  network_swap(keys, 1, 5);
  network_swap(keys, 9, 13);
  network_swap(keys, 2, 6);
  network_swap(keys, 3, 7);
  network_swap(keys, 0, 8);
  network_swap(keys, 1, 9);
  network_swap(keys, 2, 10);
  network_swap(keys, 3, 11);
  network_swap(keys, 4, 12);
  network_swap(keys, 5, 13);
  network_swap(keys, 5, 10);
  network_swap(keys, 6, 9);
  network_swap(keys, 3, 12);
  network_swap(keys, 7, 11);
  network_swap(keys, 1, 2);
  network_swap(keys, 4, 8);
  network_swap(keys, 1, 4);
  network_swap(keys, 7, 13);
  network_swap(keys, 2, 8);
  network_swap(keys, 2, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 13);
  network_swap(keys, 3, 8);
  network_swap(keys, 7, 12);
  network_swap(keys, 6, 8);
  network_swap(keys, 10, 12);
  network_swap(keys, 3, 5);
  network_swap(keys, 7, 9);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 7, 8);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 12);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
}

__attribute__((always_inline))
inline void network_sort_15(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 10, 11);
  network_swap(keys, 12, 13);
  network_swap(keys, 0, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 10);
  network_swap(keys, 12, 14);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 9, 11);
  network_swap(keys, 0, 4);
  network_swap(keys, 8, 12);
  network_swap(keys, 1, 5);
  network_swap(keys, 9, 13);
  network_swap(keys, 2, 6);
  network_swap(keys, 10, 14);
  network_swap(keys, 3, 7);
  network_swap(keys, 0, 8);
  network_swap(keys, 1, 9);
  network_swap(keys, 2, 10);
  network_swap(keys, 3, 11);
  network_swap(keys, 4, 12);
  network_swap(keys, 5, 13);
  network_swap(keys, 6, 14);
  network_swap(keys, 5, 10);
  network_swap(keys, 6, 9);
  network_swap(keys, 3, 12);
  network_swap(keys, 13, 14);
  network_swap(keys, 7, 11);
  network_swap(keys, 1, 2);
  network_swap(keys, 4, 8);
  network_swap(keys, 1, 4);
  network_swap(keys, 7, 13);
  network_swap(keys, 2, 8);
  network_swap(keys, 11, 14);
  network_swap(keys, 2, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 13);
  network_swap(keys, 3, 8);
  network_swap(keys, 7, 12);
  network_swap(keys, 6, 8);
  network_swap(keys, 10, 12);
  network_swap(keys, 3, 5);
  network_swap(keys, 7, 9);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 7, 8);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 12);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
}

__attribute__((always_inline))
inline void network_sort_16(int* keys)
{
  network_swap(keys, 0, 1);
  network_swap(keys, 2, 3);
  network_swap(keys, 4, 5);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
  network_swap(keys, 10, 11);
  network_swap(keys, 12, 13);
  network_swap(keys, 14, 15);
  network_swap(keys, 0, 2);
  network_swap(keys, 4, 6);
  network_swap(keys, 8, 10);
  network_swap(keys, 12, 14);
  network_swap(keys, 1, 3);
  network_swap(keys, 5, 7);
  network_swap(keys, 9, 11);
  network_swap(keys, 13, 15);
  network_swap(keys, 0, 4);
  network_swap(keys, 8, 12);
  network_swap(keys, 1, 5);
  network_swap(keys, 9, 13);
  network_swap(keys, 2, 6);
  network_swap(keys, 10, 14);
  network_swap(keys, 3, 7);
  network_swap(keys, 11, 15);
  network_swap(keys, 0, 8);
  network_swap(keys, 1, 9);
  network_swap(keys, 2, 10);
  network_swap(keys, 3, 11);
  network_swap(keys, 4, 12);
  network_swap(keys, 5, 13);
  network_swap(keys, 6, 14);
  network_swap(keys, 7, 15);
  network_swap(keys, 5, 10);
  network_swap(keys, 6, 9);
  network_swap(keys, 3, 12);
  network_swap(keys, 13, 14);
  network_swap(keys, 7, 11);
  network_swap(keys, 1, 2);
  network_swap(keys, 4, 8);
  network_swap(keys, 1, 4);
  network_swap(keys, 7, 13);
  network_swap(keys, 2, 8);
  network_swap(keys, 11, 14);
  network_swap(keys, 2, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 13);
  network_swap(keys, 3, 8);
  network_swap(keys, 7, 12);
  network_swap(keys, 6, 8);
  network_swap(keys, 10, 12);
  network_swap(keys, 3, 5);
  network_swap(keys, 7, 9);
  network_swap(keys, 3, 4);
  network_swap(keys, 5, 6);
  network_swap(keys, 7, 8);
  network_swap(keys, 9, 10);
  network_swap(keys, 11, 12);
  network_swap(keys, 6, 7);
  network_swap(keys, 8, 9);
}

__attribute__((noinline))
void network_sort(int* keys, const int key_count)
{
  static const network_sort_t sorts[] = {
    0,
    0,
    network_sort_02,
    network_sort_03,
    network_sort_04,
    network_sort_05,
    network_sort_06,
    network_sort_07,
    network_sort_08,
    network_sort_09,
    network_sort_10,
    network_sort_11,
    network_sort_12,
    network_sort_13,
    network_sort_14,
    network_sort_15,
    network_sort_16
  };

  const int sort_count = sizeof(sorts) / sizeof(sorts[0]);
  if (key_count < sort_count)
  {
    const network_sort_t sort = sorts[key_count];
    if (sort != 0)
    {
      sort(keys);
    }
  }
}
