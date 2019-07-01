#pragma once

typedef int* (*quick_pivot_t)(int* const keys_begin, int* const keys_end);
int* quick_middle_pivot(int* const keys_begin, int* const keys_end);
int* quick_median3_pivot(int* const keys_begin, int* const keys_end);

void quick_sort(int* const keys, const int key_count, const quick_pivot_t quick_pivot);
