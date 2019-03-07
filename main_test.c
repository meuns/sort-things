#include <stdio.h>

#include "test.h"

#include "bubble_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

void wrap_merge_sort(int* keys, const int key_count)
{
  int temp_keys[key_count];
  merge_sort(keys, key_count, temp_keys);
}

typedef void (*sort_function_t)(int* keys, const int key_count);

int main()
{
  const int max_key_count = 3871;
  int keys[max_key_count];
  
  sort_function_t sort_functions[] =
  {
    /*bubble_sort,
    heap_sort,
    insert_sort,
    wrap_merge_sort,*/
    quick_sort
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
      
      //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); }
      //printf("\n");
      
      sort_function(keys, key_count);
      
      if (!keys_are_sorted(keys, key_count))
      {
        printf("Testing function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); }
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
