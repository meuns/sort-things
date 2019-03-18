#include <stdio.h>
#include "count_sort.h"

int main()
{
	signed char keys[] = {
		11, 12, 0, 2,
		5, 4, 14, 1,
		9, 9, 6, 6,
		1, 2, 3, 17
	};
	
	int key_count = sizeof(keys) / sizeof(keys[0]);
  
  signed char sorted_keys[key_count];
	
	count_sort(keys, key_count, sorted_keys);
  
  printf("{");
	
	for (int key_index = 0; key_index < key_count - 1; ++key_index)
	{
		printf("%d, ", (int)sorted_keys[key_index]);
	}
	
  printf("%d}\n", (int)sorted_keys[key_count - 1]);

  return 0;
}
