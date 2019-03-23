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

void wrap_radix_sort_halfbyte(int* keys, const int key_count)
{
  int temp_keys[key_count];
  radix_sort_halfbyte(keys, key_count, temp_keys);
}

void wrap_radix_sort_byte(int* keys, const int key_count)
{
  int temp_keys[key_count];
  radix_sort_byte(keys, key_count, temp_keys);
}

void wrap_radix_sort_short(int* keys, const int key_count)
{
  int temp_keys[key_count];
  radix_sort_short(keys, key_count, temp_keys);
}

typedef struct
{
  sort_function_int_t sort_function;
  const char* sort_name;
}
test_int_t;

typedef struct
{
  sort_function_char_t sort_function;
  const char* sort_name;
}
test_char_t;

int main()
{
  const int max_key_count = 3871;
  
  test_int_t tests_int[] =
  {
    {wrap_bubble_sort, "bubble_sort"},
    {wrap_heap_sort, "heap_sort"},
    {wrap_insert_sort, "insert_sort"},
    {wrap_merge_sort, "merge_sort"},
    {wrap_quick_sort, "quick_sort"},
    {wrap_radix_sort_halfbyte, "radix_sort_halfbyte"},
    {wrap_radix_sort_byte, "radix_sort_byte"},
    {wrap_radix_sort_short, "radix_sort_short"}
  };
  
  test_char_t tests_char[] =
  {
    {wrap_count_sort, "count_sort"}
  };
  
  const int sort_count_int = sizeof(tests_int) / sizeof(tests_int[0]);
  const int sort_count_char = sizeof(tests_char) / sizeof(tests_char[0]);
  
  const int test_count = max_key_count * (sort_count_int + sort_count_char);
  int remaining_test_count = test_count;
  int last_percent_print = -1;
  
  // int keys
  int keys[max_key_count];
  int sorted_keys[max_key_count];
  
  for (int sort_index = 0; sort_index < sort_count_int; ++sort_index)
  {
    const test_int_t test_int = tests_int[sort_index];
    const sort_function_int_t sort_function = test_int.sort_function;
    const char* sort_name = test_int.sort_name;

    printf("\nTesting %s\n", sort_name);

    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      test_generate_keys_int(keys, key_count, 42);
      memcpy(sorted_keys, keys, sizeof(keys));

      sort_function(sorted_keys, key_count);

      if (!test_key_counts_are_equal_int(keys, sorted_keys, key_count))
      {
        printf("\nTesting histogram function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
        return 1;
      }

      if (!test_keys_are_sorted_int(sorted_keys, key_count))
      {
        printf("\nTesting sort function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys[key_index]); } printf("\n");
        return 1;
      }

      const int percent_print = (int)((((float)remaining_test_count--) / test_count) * 100);
      if (percent_print != last_percent_print)
      {
        last_percent_print = percent_print;
        printf(".");
        fflush(stdout);
      }
    }
  }
  
  // char keys
  signed char keys_char[max_key_count];
  signed char sorted_keys_char[max_key_count];
  
  for (int sort_index = 0; sort_index < sort_count_char; ++sort_index)
  {
    const test_char_t test_char = tests_char[sort_index];
    const sort_function_char_t sort_function = test_char.sort_function;
    const char* sort_name = test_char.sort_name;

    printf("\nTesting %s\n", sort_name);

    for (int key_count = 0; key_count < max_key_count; ++key_count)
    {
      test_generate_keys_char(keys_char, key_count, 42);
      memcpy(sorted_keys_char, keys_char, sizeof(keys_char));

      sort_function(sorted_keys_char, key_count);

      if (!test_key_counts_are_equal_char(keys_char, sorted_keys_char, key_count))
      {
        printf("\nTesting histogram function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys_char[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys_char[key_index]); } printf("\n");
        return 1;
      }
      
      if (!test_keys_are_sorted_char(sorted_keys_char, key_count))
      {
        printf("\nTesting sort function %d and key count %d failed...\n", sort_index, key_count);
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", keys_char[key_index]); } printf("\n");
        for (int key_index = 0; key_index < key_count; ++key_index) { printf("%d, ", sorted_keys_char[key_index]); } printf("\n");
        return 1;
      }
      
      const int percent_print = (int)((((float)remaining_test_count--) / test_count) * 100);
      if (percent_print != last_percent_print)
      {
        last_percent_print = percent_print;
        printf(".");
        fflush(stdout);
      }
    }
  }

  printf("\n");

  return 0;
}
