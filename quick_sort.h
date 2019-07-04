#pragma once

typedef int (*quick_compare_t)(const void* left_key, const void* right_key);
int quick_compare_default(const void* left_key, const void* right_key);

typedef void (*quick_copy_t)(void* to_key, const void* from_key);
void quick_copy_default(void* to_key, const void* from_key);

typedef char* (*quick_pivot_t)(char* const keys_begin, char* const keys_end, const quick_compare_t quick_compare);
char* quick_middle_pivot(char* const keys_begin, char* const keys_end, const quick_compare_t quick_compare);
char* quick_median3_pivot(char* const keys_begin, char* const keys_end, const quick_compare_t quick_compare);

void quick_sort(void* const keys, const int key_count, const int key_size, const quick_pivot_t quick_pivot, const quick_compare_t quick_compare, const quick_copy_t quick_copy);
