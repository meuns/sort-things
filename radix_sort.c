#include "radix_sort.h"

#include <limits.h>

// Temporary workaround linking issue on _WIN32
#if defined(_WIN32)
  #define WA_INLINE
#else
  #define WA_INLINE inline
#endif

typedef int (*radix_key_t)(const int key, const int byte_index);

typedef int (*radix_should_sort_digit_t)(int* restrict histogram, const int histogram_size, const int key_count);

__attribute__((always_inline))
WA_INLINE int radix_should_sort_digit(int* restrict histogram, const int histogram_size, const int key_count)
{
  // Using this requires some knowledges about the key distribution or 
  // this is a performance loss even for very large array (1<<20 uniformly distributed keys)
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    if (histogram[bin_index] == key_count)
    {
      return 0;
    }
  }

  return 1;
}

__attribute__((always_inline))
WA_INLINE int radix_always_sort_digit(int* restrict histogram __attribute__((unused)), const int histogram_size __attribute__((unused)), const int key_count __attribute__((unused)))
{
  return 1;
}

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

__attribute__((noinline))
void radix_sort_halfbyte(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = 16;
  int histogram0[histogram_size];
  int histogram1[histogram_size];
  int histogram2[histogram_size];
  int histogram3[histogram_size];
  int histogram4[histogram_size];
  int histogram5[histogram_size];
  int histogram6[histogram_size];
  int histogram7[histogram_size];
  
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram0[bin_index] = 0;
    histogram1[bin_index] = 0;
    histogram2[bin_index] = 0;
    histogram3[bin_index] = 0;
    histogram4[bin_index] = 0;
    histogram5[bin_index] = 0;
    histogram6[bin_index] = 0;
    histogram7[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = keys[key_index];
    const int key_bin0 = radix_key_halfbyteX(key, 0);
    const int key_bin1 = radix_key_halfbyteX(key, 1);
    const int key_bin2 = radix_key_halfbyteX(key, 2);
    const int key_bin3 = radix_key_halfbyteX(key, 3);
    const int key_bin4 = radix_key_halfbyteX(key, 4);
    const int key_bin5 = radix_key_halfbyteX(key, 5);
    const int key_bin6 = radix_key_halfbyteX(key, 6);
    const int key_bin7 = radix_key_halfbyte7(key, 7);
    histogram0[key_bin0]++;
    histogram1[key_bin1]++;
    histogram2[key_bin2]++;
    histogram3[key_bin3]++;
    histogram4[key_bin4]++;
    histogram5[key_bin5]++;
    histogram6[key_bin6]++;
    histogram7[key_bin7]++;
  }
  
  for (int bin_index = 1; bin_index < histogram_size; ++bin_index)
  {
    const int previous_bin_index = bin_index - 1;
    histogram0[bin_index] += histogram0[previous_bin_index];
    histogram1[bin_index] += histogram1[previous_bin_index];
    histogram2[bin_index] += histogram2[previous_bin_index];
    histogram3[bin_index] += histogram3[previous_bin_index];
    histogram4[bin_index] += histogram4[previous_bin_index];
    histogram5[bin_index] += histogram5[previous_bin_index];
    histogram6[bin_index] += histogram6[previous_bin_index];
    histogram7[bin_index] += histogram7[previous_bin_index];
  }
  
  int* input_keys = keys;
  int* output_keys = temp_keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 0);
    output_keys[--histogram0[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 1);
    output_keys[--histogram1[key_bin]] = key;
  }

  input_keys = keys;
  output_keys = temp_keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 2);
    output_keys[--histogram2[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 3);
    output_keys[--histogram3[key_bin]] = key;
  }

  input_keys = keys;
  output_keys = temp_keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 4);
    output_keys[--histogram4[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 5);
    output_keys[--histogram5[key_bin]] = key;
  }

  input_keys = keys;
  output_keys = temp_keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyteX(key, 6);
    output_keys[--histogram6[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_halfbyte7(key, 7);
    output_keys[--histogram7[key_bin]] = key;
  }
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

__attribute__((noinline))
void radix_sort_byte(int* restrict keys, const int key_count, int* restrict temp_keys, radix_should_sort_digit_t should_sort_digit)
{
  const int histogram_size = UCHAR_MAX + 1;
  int histogram0[histogram_size];
  int histogram1[histogram_size];
  int histogram2[histogram_size];
  int histogram3[histogram_size];
  
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram0[bin_index] = 0;
    histogram1[bin_index] = 0;
    histogram2[bin_index] = 0;
    histogram3[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = keys[key_index];
    const int key_bin0 = radix_key_byteX(key, 0);
    const int key_bin1 = radix_key_byteX(key, 1);
    const int key_bin2 = radix_key_byteX(key, 2);
    const int key_bin3 = radix_key_byte3(key, 3);
    histogram0[key_bin0]++;
    histogram1[key_bin1]++;
    histogram2[key_bin2]++;
    histogram3[key_bin3]++;
  }

  const int must_sort0 = should_sort_digit(histogram0, histogram_size, key_count);
  const int must_sort1 = should_sort_digit(histogram1, histogram_size, key_count);
  const int must_sort2 = should_sort_digit(histogram2, histogram_size, key_count);
  const int must_sort3 = should_sort_digit(histogram3, histogram_size, key_count);
  
  for (int bin_index = 1; bin_index < histogram_size; ++bin_index)
  {
    const int previous_bin_index = bin_index - 1;
    histogram0[bin_index] += histogram0[previous_bin_index];
    histogram1[bin_index] += histogram1[previous_bin_index];
    histogram2[bin_index] += histogram2[previous_bin_index];
    histogram3[bin_index] += histogram3[previous_bin_index];
  }
  
  int* input_keys = keys;
  int* output_keys = temp_keys;

  if (must_sort0)
  {
    for (int key_index = key_count - 1; key_index >= 0; --key_index)
    {
      const int key = input_keys[key_index];
      const int key_bin = radix_key_byteX(key, 0);
      output_keys[--histogram0[key_bin]] = key;
    }

    input_keys = temp_keys;
    output_keys = keys;
  }

  if (must_sort1)
  {
    for (int key_index = key_count - 1; key_index >= 0; --key_index)
    {
      const int key = input_keys[key_index];
      const int key_bin = radix_key_byteX(key, 1);
      output_keys[--histogram1[key_bin]] = key;
    }

    input_keys = keys;
    output_keys = temp_keys;
  }

  if (must_sort2)
  {
    for (int key_index = key_count - 1; key_index >= 0; --key_index)
    {
      const int key = input_keys[key_index];
      const int key_bin = radix_key_byteX(key, 2);
      output_keys[--histogram2[key_bin]] = key;
    }

    input_keys = temp_keys;
    output_keys = keys;
  }

  if (must_sort3)
  {
    for (int key_index = key_count - 1; key_index >= 0; --key_index)
    {
      const int key = input_keys[key_index];
      const int key_bin = radix_key_byte3(key, 3);
      output_keys[--histogram3[key_bin]] = key;
    }

    input_keys = temp_keys;
    output_keys = keys;
  }

  if (output_keys == keys)
  {
    for (int key_index = 0; key_index < key_count; ++key_index)
    {
      output_keys[key_index] = input_keys[key_index];
    }
  }
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

__attribute__((noinline))
void radix_sort_short(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = USHRT_MAX + 1;
  int histogram0[histogram_size];
  int histogram1[histogram_size];
    
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram0[bin_index] = 0;
    histogram1[bin_index] = 0;
  }
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = keys[key_index];
    const int key_bin0 = radix_key_short0(key, 0);
    const int key_bin1 = radix_key_short1(key, 1);
    histogram0[key_bin0]++;
    histogram1[key_bin1]++;
  }
  
  for (int bin_index = 1; bin_index < histogram_size; ++bin_index)
  {
    const int previous_bin_index = bin_index - 1;
    histogram0[bin_index] += histogram0[previous_bin_index];
    histogram1[bin_index] += histogram1[previous_bin_index];
  }
  
  int* input_keys = keys;
  int* output_keys = temp_keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_short0(key, 0);
    output_keys[--histogram0[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = key_count - 1; key_index >= 0; --key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_short1(key, 1);
    output_keys[--histogram1[key_bin]] = key;
  }
}
