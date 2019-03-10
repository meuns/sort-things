#pragma once

void generate_keys(int* keys, const int key_count, const unsigned int seed);

int key_counts_are_equal(int* keys, int* sorted_keys, const int key_count);

int keys_are_sorted(int* const keys, const int key_count);
