
void bubble_sort(int* keys, int key_count)
{
  for (int min_index = 0; min_index < key_count; ++min_index)
  {
    int min_key = keys[min_index];

    for (int current_index = min_index + 1; current_index < key_count; ++current_index)
    {
      int current_key = keys[current_index];
      if (current_key < min_key)
      {
        keys[min_index] = current_key;
        keys[current_index] = min_key;
        min_key = current_key;
      }
    }
  }
}
