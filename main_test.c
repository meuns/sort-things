#include <stdio.h>
#include <string.h>

#include "test.h"

#include "bubble_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "count_sort.h"

typedef void (*sort_function_int_t)(int* keys, const int key_count);
typedef void (*sort_function_char_t)(signed char* keys, const int key_count);

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

void wrap_count_sort(signed char* keys, const int key_count)
{
  signed char temp_keys[key_count];
  count_sort(keys, key_count, temp_keys);
  memcpy(keys, temp_keys, sizeof(temp_keys));
}

void wrap_radix_sort(int* keys, const int key_count)
{
  printf("%d\n", key_count);
  int temp_keys[key_count];
  radix_sort(keys, key_count, temp_keys);
}

int main()
{
  const int max_key_count = 3871;
  
  sort_function_int_t sort_functions_int[] =
  {
    //wrap_bubble_sort,
    //wrap_heap_sort,
    //wrap_insert_sort,
    //wrap_merge_sort,
    //wrap_quick_sort,
    wrap_radix_sort
  };
  
  sort_function_char_t sort_functions_char[] =
  {
    wrap_count_sort
  };
  
  const int sort_count_int = sizeof(sort_functions_int) / sizeof(sort_functions_int[0]);
  const int sort_count_char = sizeof(sort_functions_char) / sizeof(sort_functions_char[0]);
  
  const int test_count = max_key_count * (sort_count_int + sort_count_char);
  int remaining_test_count = test_count;
  int last_percent_print = -1;
  
  // int keys
  int keys[max_key_count];
  int sorted_keys[max_key_count];
  
  for (int sort_index = 0; sort_index < sort_count_int; ++sort_index)
  {
    sort_function_int_t sort_function = sort_functions_int[sort_index];

    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      generate_keys_int(keys, key_count, 42);
      memcpy(sorted_keys, keys, sizeof(keys));

      sort_function(sorted_keys, key_count);

      if (!key_counts_are_equal_int(keys, sorted_keys, key_count))
      {
        printf("Testing histogram function %d and key count %d failed...\n", sort_index, key_count);
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
        return 1;
      }

      if (!keys_are_sorted_int(sorted_keys, key_count))
      {
        printf("Testing sort function %d and key count %d failed...\n", sort_index, key_count);
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
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
  
  // char keys
  signed char keys_char[max_key_count];
  signed char sorted_keys_char[max_key_count];
  
  for (int sort_index = 0; sort_index < sort_count_char; ++sort_index)
  {
    //sort_function_char_t sort_function = sort_functions_char[sort_index];
    
    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      generate_keys_char(keys_char, key_count, 42);
      memcpy(sorted_keys_char, keys_char, sizeof(keys_char));

      //sort_function(sorted_keys_char, key_count);

      if (!key_counts_are_equal_char(keys_char, sorted_keys_char, key_count))
      {
        printf("Testing histogram function %d and key count %d failed...\n", sort_index, key_count);
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys_char[key_index]); } printf("\n");
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys_char[key_index]); } printf("\n");
        return 1;
      }
      
      if (!keys_are_sorted_char(sorted_keys_char, key_count))
      {
        printf("Testing sort function %d and key count %d failed...\n", sort_index, key_count);
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys_char[key_index]); } printf("\n");
        //for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys_char[key_index]); } printf("\n");
        return 1;
      }
      
      printf("Testing function %d and key count %d...\n", sort_index, key_count);

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
