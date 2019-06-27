#include "merge_hybrid_sort.h"

#include "merge_sort.h"
#include "network_sort.h"

__attribute__((noinline))
void merge_sort_hybrid(int* keys, const int key_count, int* temp_keys)
{
  int presort_index = 0;
  int next_presort_index = 16;
  while (next_presort_index < key_count)
  {
    network_sort_16(&keys[presort_index]);
    presort_index = next_presort_index;
    next_presort_index += 16;
  }

  network_sort(&keys[presort_index], key_count - presort_index);

  if (key_count <= 16)
  {
    return;
  }

  int* input_keys = keys;
  int* output_keys = temp_keys;  
  for (int left_key_count = 16; left_key_count <= key_count; left_key_count <<= 1)
  {
    int right_key_count = left_key_count;
    int merge_index = 0;
    int next_merge_index = merge_index + left_key_count + right_key_count;
    while (next_merge_index <= key_count)
    {
      merge_keys(4, &input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare_default, merge_copy_default);
      merge_index = next_merge_index;
      next_merge_index = merge_index + left_key_count + right_key_count;
    }
    
    if (merge_index + left_key_count < key_count)
    {
      right_key_count = key_count - (merge_index + left_key_count);
      merge_keys(4, &input_keys[merge_index], left_key_count, &input_keys[merge_index + left_key_count], right_key_count, &output_keys[merge_index], merge_compare_default, merge_copy_default);
    }
    else
    {
      for (int copy_index = merge_index; copy_index < key_count; ++copy_index)
      {
        output_keys[copy_index] = input_keys[copy_index];
      }
    }

    int* swap_keys = input_keys;
    input_keys = output_keys;
    output_keys = swap_keys;
  }

  if (input_keys == temp_keys)
  {
    for (int copy_index = 0; copy_index < key_count; ++copy_index)
    {
      keys[copy_index] = temp_keys[copy_index];
    }
  }
}
