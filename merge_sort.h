#pragma once

typedef int (*merge_compare_keys_t)(const void* left_key, const void* right_key);
int merge_compare_default(const void* left_key, const void* right_key);

typedef void (*merge_copy_t)(void* to_key, const void* from_key);
void merge_copy_default(void* to_key, const void* from_key);

void merge_keys(void* restrict left_keys, const int left_key_count, void* restrict right_keys, const int right_key_count, int* restrict merged_keys, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy);

void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy);
