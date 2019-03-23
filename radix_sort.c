#include "radix_sort.h"

#include <limits.h>

typedef int (*radix_key_t)(const int key, const int byte_index);

__attribute__((always_inline))
static inline int radix_key_halfbyte7(const int key, const int byte_index __attribute__((unused)))
{
  const unsigned int flipped_key = (unsigned int)key ^ 0x80000000U;
  return (int)((flipped_key & 0xF0000000) >> 28);
}

__attribute__((always_inline))
static inline int radix_key_halfbyteX(const int key, const int pass_index)
{
  const unsigned int mask = 0x0000000F;
  const int bit_shift = pass_index << 2;
  return (int)(((unsigned int)key & (mask << bit_shift)) >> bit_shift);
}

__attribute__((always_inline))
static inline int radix_key_byte3(const int key, const int pass_index __attribute__((unused)))
{
  const unsigned int flipped_key = (unsigned int)key ^ 0x80000000U;
  return (int)((flipped_key & 0xFF000000) >> 24);
}

__attribute__((always_inline))
static inline int radix_key_byteX(const int key, const int pass_index)
{
  const unsigned int mask = 0x000000FF;
  const int bit_shift = pass_index << 3;
  return (int)(((unsigned int)key & (mask << bit_shift)) >> bit_shift);
}

__attribute__((always_inline))
static inline int radix_key_short1(const int key, const int pass_index __attribute__((unused)))
{
  const unsigned int flipped_key = (unsigned int)key ^ 0x80000000U;
  return (int)((flipped_key & 0xFFFF0000) >> 16);
}

__attribute__((always_inline))
static inline int radix_key_short0(const int key, const int pass_index __attribute__((unused)))
{
  return (int)((unsigned int)key & 0x0000FFFF);
}

__attribute__((always_inline))
static inline void radix_sort_pass(int* restrict input_keys, int* restrict output_keys, const int key_count, const int histogram_size, radix_key_t radix_key_bin, const int byte_index)
{
  int histogram[histogram_size];
  
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key_bin = radix_key_bin(input_keys[key_index], byte_index);
    histogram[key_bin]++;
  }
  
  for (int bin_index = 1; bin_index < histogram_size; ++bin_index)
  {
    histogram[bin_index] += histogram[bin_index - 1];
  }
  
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_bin(key, byte_index);
    output_keys[--histogram[key_bin]] = key;
  }
}

__attribute__((noinline))
void radix_sort_halfbyte(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = 16;
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_halfbyteX, 0);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_halfbyteX, 1);
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_halfbyteX, 2);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_halfbyteX, 3);
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_halfbyteX, 4);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_halfbyteX, 5);
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_halfbyteX, 6);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_halfbyte7, 7);
}

__attribute__((noinline))
void radix_sort_byte(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = UCHAR_MAX + 1;
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_byteX, 0);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_byteX, 1);
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_byteX, 2);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_byte3, 3);
}

__attribute__((noinline))
void radix_sort_short(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = USHRT_MAX + 1;
  radix_sort_pass(keys, temp_keys, key_count, histogram_size, radix_key_short0, 0);
  radix_sort_pass(temp_keys, keys, key_count, histogram_size, radix_key_short1, 1);
}
