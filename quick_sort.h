#pragma once

typedef int (*quick_pivot_index_t)(int* keys, const int key_count);

int quick_middle_pivot_index(int* keys, const int key_count);
int quick_median3_pivot_index(int* keys, const int key_count);

void quick_sort(int* keys, const int key_count, quick_pivot_index_t quick_pivot_index);
