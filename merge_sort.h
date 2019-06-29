#pragma once

void merge_keys(int* restrict left_keys, const int left_key_count, int* restrict right_keys, const int right_key_count, int* restrict merged_keys);

void merge_sort(int* restrict keys, const int key_count, int* restrict temp_keys);
