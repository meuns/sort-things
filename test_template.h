
#if !defined(CONCAT_SUFFIX) || !defined(KEY_TYPE)
  #error Please define CONCAT_SUFFIX and KEY_TYPE before including test_template.h
#endif

void CONCAT_SUFFIX(test_generate_keys)(KEY_TYPE* keys, const long long int key_count, const unsigned int seed);

int CONCAT_SUFFIX(test_key_counts_are_equal)(KEY_TYPE* keys, KEY_TYPE* sorted_keys, const long long int key_count);

int CONCAT_SUFFIX(test_keys_are_sorted)(KEY_TYPE* const keys, const long long int key_count);
