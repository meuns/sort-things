#pragma once

typedef int (*merge_compare_keys_t)(int left_key, int right_key);
int merge_compare_default(int left_key, int right_key);

typedef void (*merge_copy_t)(void* to_key, void* from_key);
void merge_copy_default(void* to_key, void* from_key);

void merge_keys(int* restrict left_keys, const int left_key_count, int* restrict right_keys, const int right_key_count, int* restrict merged_keys, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy);

void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy);
