#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

void std_sort(int* keys, const int key_count);

void std_stable_sort(int* keys, const int key_count);

void std_qsort(int* keys, const int key_count);

#ifdef __cplusplus
}
#endif
