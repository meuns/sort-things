
#if !defined(CONCAT_SUFFIX) || !defined(KEY_TYPE)
  #error Please define CONCAT_SUFFIX and KEY_TYPE before including test_template.c
#endif

void CONCAT_SUFFIX(generate_keys)(KEY_TYPE* keys, const int key_count, const unsigned int seed)
{
  srand(seed);
  
  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = (KEY_TYPE)(rand() % 256) - 128;
  }
}

static inline KEY_TYPE CONCAT_SUFFIX(min)(KEY_TYPE a, KEY_TYPE b)
{
  return a < b ? a : b;
}

static inline KEY_TYPE CONCAT_SUFFIX(max)(KEY_TYPE a, KEY_TYPE b)
{
  return a > b ? a : b;
}

int CONCAT_SUFFIX(key_counts_are_equal)(KEY_TYPE* keys, KEY_TYPE* sorted_keys, const int key_count)
{
  KEY_TYPE min_key = keys[0];
  KEY_TYPE max_key = keys[0];

  for (int key_index = 1; key_index < key_count; ++key_index)
  {
    min_key = CONCAT_SUFFIX(min)(min_key, keys[key_index]);
    max_key = CONCAT_SUFFIX(max)(max_key, keys[key_index]);
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    min_key = CONCAT_SUFFIX(min)(min_key, sorted_keys[key_index]);
    max_key = CONCAT_SUFFIX(max)(max_key, sorted_keys[key_index]);
  }

  const int histogram_size = max_key - min_key + 1;

  int* histogram = (int*)malloc(sizeof(int) * histogram_size);
  int* sorted_histogram = (int*)malloc(sizeof(int) * histogram_size);

  for (int entry_index = 0; entry_index < histogram_size; ++entry_index)
  {
    histogram[entry_index] = 0;
    sorted_histogram[entry_index] = 0;
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    histogram[keys[key_index] - min_key]++;
  }

  for (int key_index = 0; key_index < key_count; ++key_index)
  {
    sorted_histogram[sorted_keys[key_index] - min_key]++;
  }

  int result = 1;
  for (int entry_index = 0; entry_index < histogram_size; ++entry_index)
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

int CONCAT_SUFFIX(keys_are_sorted)(KEY_TYPE* const keys, const int key_count)
{
  KEY_TYPE key = keys[0];
  for (int key_index = 1; key_index < key_count; ++key_index)
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
