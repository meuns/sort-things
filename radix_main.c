#include <stdio.h>
#include "count_sort.h"

int main()
{
	unsigned char keys[] = {
		11, 12, 0, 2,
		5, 4, 14, 1,
		9, 9, 6, 6,
		1, 2, 3, 17
	};
	
	int key_count = sizeof(keys) / sizeof(keys[0]);
  
  unsigned char sorted_keys[key_count];
	
	count_sort(keys, sorted_keys, key_count);
	
	for (int key_index = 0; key_index < key_count; ++key_index)
	{
		printf("%d ", sorted_keys[key_index]);
	}
	
	printf("\n");

  return 0;
}
