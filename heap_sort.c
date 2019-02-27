#include "heap_sort.h"

__attribute__((always_inline))
static inline int heap_parent_index(const int heap_index)
{
    return (heap_index - 1) >> 1;
}

__attribute__((always_inline))
static inline int heap_left_child_index(const int heap_index)
{
    return (heap_index << 1) + 1;
}

__attribute__((always_inline))
static inline int heap_right_child_index(const int heap_index)
{
    return (heap_index << 1) + 2;
}

__attribute__((always_inline))
static inline void heap_build_up(int* const heap_root, const int heap_last_index, const int new_key)
{
    int current_index = heap_last_index;
    int parent_index = heap_parent_index(current_index);
    int parent_key = heap_root[parent_index];

    while (current_index > 0 && parent_key < new_key)
    {
        heap_root[current_index] = parent_key;
        current_index = parent_index;
        parent_index = heap_parent_index(parent_index);
        parent_key = heap_root[parent_index];
    }

    heap_root[current_index] = new_key;
}

__attribute__((always_inline))
static inline void heap_fix_down(int* const key_heap_root, const int heap_last_element, const int fix_key)
{
    int current_index = 0;
    int left_child_index = heap_left_child_index(current_index);
    int right_child_index = heap_right_child_index(current_index);

    while (right_child_index <= heap_last_element)
    {
        const int left_child_key = key_heap_root[left_child_index];
        const int right_child_key = key_heap_root[right_child_index];

        int min_index;
        int min_key;
        if (right_child_key > left_child_key)
        {
            min_index = right_child_index;
            min_key = right_child_key;
        }
        else
        {
            min_index = left_child_index;
            min_key = left_child_key;
        }
        
        if (min_key > fix_key)
        {
            key_heap_root[current_index] = min_key;
            current_index = min_index;

            left_child_index = heap_left_child_index(current_index);    
            right_child_index = heap_right_child_index(current_index);
        }
        else
        {
            left_child_index = right_child_index = heap_last_element + 1;
        }
    }

    if (left_child_index <= heap_last_element)
    {
        const int left_child_key = key_heap_root[left_child_index];
        
        if (fix_key < left_child_key)
        {
            key_heap_root[current_index] = left_child_key;            
            current_index = left_child_key;
        }
    }
    
    key_heap_root[current_index] = fix_key;
}

void heap_sort(int* keys, const int key_count)
{
    for (int heap_last_element = 0; heap_last_element < key_count; ++heap_last_element)
    {
        heap_build_up(keys, heap_last_element, keys[heap_last_element]);
    }

    for (int heap_last_element = key_count - 1; heap_last_element >= 0; --heap_last_element)
    {
        const int min_key = keys[0];
        heap_fix_down(keys, heap_last_element, keys[heap_last_element]);
        keys[heap_last_element] = min_key;
    }
}
