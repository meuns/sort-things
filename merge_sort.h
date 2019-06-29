#pragma once

typedef int (*merge_compare_keys_t)(const void* left_key, const void* right_key);
int merge_compare_default(const void* left_key, const void* right_key);

typedef void (*merge_copy_t)(void* to_key, const void* from_key);
void merge_copy_default(void* to_key, const void* from_key);

void merge_keys(const int key_size, void* restrict left_keys, const int left_keys_size, void* restrict right_keys, const int right_keys_size, void* restrict merged_keys, const merge_compare_keys_t merge_compare, const merge_copy_t merge_copy);

void merge_sort(void* restrict keys, const int key_count, const int key_size, void* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy);
void merge_sort_4(void* restrict keys, const int key_count, void* restrict temp_keys, const merge_compare_keys_t merge_compare, merge_copy_t merge_copy);
