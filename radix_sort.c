#include "radix_sort.h"

#include "debug.h"

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
void radix_sort_byte(int* restrict keys, const int key_count, int* restrict temp_keys)
{
  const int histogram_size = UCHAR_MAX + 1;
  int padded_histogram0[1 + histogram_size];
  int padded_histogram1[1 + histogram_size];
  int padded_histogram2[1 + histogram_size];
  int padded_histogram3[1 + histogram_size];
  int* histogram0 = &padded_histogram0[1];
  int* histogram1 = &padded_histogram1[1];
  int* histogram2 = &padded_histogram2[1];
  int* histogram3 = &padded_histogram3[1];
  
  for (int bin_index = 0; bin_index < histogram_size; ++bin_index)
  {
    histogram0[bin_index] = 0;
    histogram1[bin_index] = 0;
    histogram2[bin_index] = 0;
    histogram3[bin_index] = 0;
  }
  
  // We shift bins to the left for incrementing in forward loops
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = -keys[key_index];
    const int key_bin0 = radix_key_byteX(key, 0);
    const int key_bin1 = radix_key_byteX(key, 1);
    const int key_bin2 = radix_key_byteX(key, 2);
    const int key_bin3 = radix_key_byte3(key, 3);
    histogram0[key_bin0 - 1]++;
    histogram1[key_bin1 - 1]++;
    histogram2[key_bin2 - 1]++;
    histogram3[key_bin3 - 1]++;
  }
  
  // We want to use preincrementation
  const int last_bin_index = histogram_size - 1;
  --histogram0[last_bin_index];
  --histogram1[last_bin_index];
  --histogram2[last_bin_index];
  --histogram3[last_bin_index];

  // We sum the histograms backwards
  for (int bin_index = last_bin_index - 1; bin_index >= 0; --bin_index)
  {
    const int next_bin_index = bin_index + 1;
    histogram0[bin_index] += histogram0[next_bin_index];
    histogram1[bin_index] += histogram1[next_bin_index];
    histogram2[bin_index] += histogram2[next_bin_index];
    histogram3[bin_index] += histogram3[next_bin_index];
  }
  
  // These loops sort keys from the biggest key to lowest so we flip the sign
  int* input_keys = keys;
  int* output_keys = temp_keys;
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = -input_keys[key_index];
    const int key_bin = radix_key_byteX(key, 0);
    output_keys[++histogram0[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_byteX(key, 1);
    output_keys[++histogram1[key_bin]] = key;
  }

  input_keys = keys;
  output_keys = temp_keys;
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_byteX(key, 2);
    output_keys[++histogram2[key_bin]] = key;
  }

  input_keys = temp_keys;
  output_keys = keys;
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    const int key = input_keys[key_index];
    const int key_bin = radix_key_byte3(key, 3);
    output_keys[++histogram3[key_bin]] = -key;
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
