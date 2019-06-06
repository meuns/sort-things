#pragma once

typedef int (*radix_should_sort_digit_t)(int* restrict histogram, const int histogram_size, const int key_count);

int radix_should_sort_digit(int* restrict histogram, const int histogram_size, const int key_count);

int radix_always_sort_digit(int* restrict histogram, const int histogram_size, const int key_count);

void radix_sort_halfbyte(int* restrict keys, const int key_count, int* restrict temp_keys);

void radix_sort_byte(int* restrict keys, const int key_count, int* restrict temp_keys, radix_should_sort_digit_t should_sort_digit);

void radix_sort_short(int* restrict keys, const int key_count, int* restrict temp_keys);
