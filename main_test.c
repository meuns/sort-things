#include <stdio.h>
#include <string.h>

#include "test.h"

#include "bubble_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

typedef void (*sort_function_t)(int* keys, const int key_count);

void wrap_bubble_sort(int* keys, const int key_count)
{
  bubble_sort(keys, key_count);
}

void wrap_heap_sort(int* keys, const int key_count)
{
  heap_sort(keys, key_count);
}

void wrap_insert_sort(int* keys, const int key_count)
{
  insert_sort(keys, key_count);
}

void wrap_merge_sort(int* keys, const int key_count)
{
  int temp_keys[key_count];
  merge_sort(keys, key_count, temp_keys);
}

void wrap_quick_sort(int* keys, const int key_count)
{
  quick_sort(keys, key_count, quick_median3_pivot_index);
}

int main()
{
  const int max_key_count = 3871;
  int keys[max_key_count];
  int sorted_keys[max_key_count];
  
  sort_function_t sort_functions[] =
  {
    wrap_bubble_sort,
    wrap_heap_sort,
    wrap_insert_sort,
    wrap_merge_sort,
    wrap_quick_sort
  };
  
  const int sort_count = sizeof(sort_functions) / sizeof(sort_functions[0]);
  
  const int test_count = max_key_count * sort_count;
  int remaining_test_count = test_count;
  int last_percent_print = -1;
  
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    sort_function_t sort_function = sort_functions[sort_index];

    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      generate_keys(keys, key_count, 42);
      memcpy(sorted_keys, keys, sizeof(keys));

      sort_function(sorted_keys, key_count);

      if (!key_counts_are_equal(keys, sorted_keys, key_count))
      {
        printf("Testing histogram function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
        return 1;
      }
      
      if (!keys_are_sorted(sorted_keys, key_count))
      {
        printf("Testing sort function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
        return 1;
      }
      
      const int percent_print = (int)((((float)remaining_test_count--) / test_count) * 100);
      if (percent_print != last_percent_print)
      {
        last_percent_print = percent_print;
        printf("%d\n", last_percent_print);
        fflush(stdout);
      }
    }
  }
  
  printf("Testing is done!\n");
  
  return 0;
}
