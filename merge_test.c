#include <stdio.h>
#include <malloc.h>

#include "merge_sort.h"
#include "test.h"

int main()
{
  const int max_key_count = 1024;
  int keys[max_key_count];
  int temp_keys[max_key_count];
  
  for (int key_count = 0; key_count < max_key_count; ++key_count)
  {
    generate_keys(keys, key_count, 42);
    
    merge_sort(keys, key_count, temp_keys);
    
    if (!keys_are_sorted(keys, key_count))
    {
      printf("FAIL\n");
    }
    
    free(temp_keys);
    free(keys);
  }

  return 0;
}
