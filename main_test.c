#include <stdio.h>

#include "test.h"

#include "bubble_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "merge_sort.h"

void wrap_merge_sort(int* keys, int key_count)
{
  int temp_keys[key_count];
  merge_sort(keys, key_count, temp_keys);
}

typedef void (*sort_function_t)(int* keys, int key_count);

int main()
{
  const int max_key_count = 871;
  int keys[max_key_count];
  
  sort_function_t sort_functions[] =
  {
      bubble_sort,
      heap_sort,
      insert_sort,
      wrap_merge_sort
  };

  const int sort_count = sizeof(sort_functions) / sizeof(sort_functions[0]);
  
  for (int sort_index = 0; sort_index < sort_count; ++sort_index)
  {
    sort_function_t sort_function = sort_functions[sort_index];

    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      generate_keys(keys, key_count, 42);
      
      sort_function(keys, key_count);
      
      if (!keys_are_sorted(keys, key_count))
      {
        printf("FAIL\n");
      }
    }
  }

  return 0;
}
