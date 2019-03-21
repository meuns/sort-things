
#if !defined(CONCAT_SUFFIX) || !defined(KEY_TYPE)
  #error Please define CONCAT_SUFFIX and KEY_TYPE before including test_template.c
#endif

int CONCAT_SUFFIX(test_key_counts_are_equal)(KEY_TYPE* keys, KEY_TYPE* sorted_keys, const long long int key_count)
{
  long long int min_key = keys[0];
  long long int max_key = keys[0];

  for (long long int key_index = 1; key_index < key_count; ++key_index)
  {
    min_key = min(min_key, keys[key_index]);
    max_key = max(max_key, keys[key_index]);
  }

  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    min_key = min(min_key, sorted_keys[key_index]);
    max_key = max(max_key, sorted_keys[key_index]);
  }

  const long long int histogram_size = max_key - min_key + 1;

  long long int* histogram = (long long int*)malloc(sizeof(long long int) * (size_t)histogram_size);
  long long int* sorted_histogram = (long long int*)malloc(sizeof(long long int) * (size_t)histogram_size);

  for (long long int entry_index = 0; entry_index < histogram_size; ++entry_index)
  {
    histogram[entry_index] = 0;
    sorted_histogram[entry_index] = 0;
  }

  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    histogram[keys[key_index] - min_key]++;
  }

  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    sorted_histogram[sorted_keys[key_index] - min_key]++;
  }

  int result = 1;
  for (long long int entry_index = 0; entry_index < histogram_size; ++entry_index)
  {
    if (histogram[entry_index] != sorted_histogram[entry_index])
    {
      result = 0;
      break;
    }
  }

  free(sorted_histogram);
  free(histogram);
  return result;
}

int CONCAT_SUFFIX(test_keys_are_sorted)(KEY_TYPE* const keys, const long long int key_count)
{
  KEY_TYPE key = keys[0];
  for (long long int key_index = 1; key_index < key_count; ++key_index)
  {
    const KEY_TYPE next_key = keys[key_index];
    if (key > next_key)
    {
      return 0;
    }
    key = next_key;
  }
  
  return 1;
}
