#pragma once

typedef int (*merge_compare_keys_t)(int left_key, int right_key);
int merge_compare_default(int left_key, int right_key);

void merge_keys(int* restrict left_keys, const int left_key_count, int* restrict right_keys, const int right_key_count, int* restrict merged_keys, const merge_compare_keys_t merge_compare);

void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys, const merge_compare_keys_t merge_compare);
