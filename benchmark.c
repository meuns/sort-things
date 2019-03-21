#include "benchmark.h"

#include <assert.h>
#include <stdlib.h>

#if defined(_WIN32)
  #include <Windows.h>
#else
  #include <time.h>
#endif

typedef struct benchmark_scope_s
{
  #if defined(_WIN32)
    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    LARGE_INTEGER frequency;
  #else
    struct timespec start_time;
    struct timespec end_time;
  #endif
}
benchmark_scope_t;

static benchmark_scope_t benchmark_ring_buffer[64];
static const int benchmark_ring_size = sizeof(benchmark_ring_buffer) / sizeof(benchmark_ring_buffer[0]);
static int benchmark_ring_head = 0;

__attribute__((noinline))
benchmark_scope_t* benchmark_begin(void)
{
  benchmark_scope_t* new_scope = &benchmark_ring_buffer[benchmark_ring_head];
  benchmark_ring_head = (benchmark_ring_head + 1) % benchmark_ring_size;

  #if defined(_WIN32)
    QueryPerformanceCounter(&new_scope->start_time);
    QueryPerformanceFrequency(&new_scope->frequency);
  #else
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &new_scope->start_time);
  #endif

  return new_scope;
}

__attribute__((noinline))
int benchmark_end(benchmark_scope_t* scope)
{
  #if defined(_WIN32)
    QueryPerformanceCounter(&scope->end_time);
    LONGLONG duration = scope->end_time.QuadPart - scope->start_time.QuadPart;
    LONGLONG duration_ms = duration / (scope->frequency.QuadPart / 1000LL);
    return (int)duration_ms;
  #else
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &scope->end_time);
    long long duration_ns = (scope->end_time.tv_sec - scope->start_time.tv_sec) * 1000000000LL + (scope->end_time.tv_nsec - scope->start_time.tv_nsec);
    long long duration_ms = duration_ns / 1000000L;
    return (int)duration_ms;
  #endif
}

__attribute__((noinline))
void benchmark_generate_random_keys(int* keys, const long long int key_count, const unsigned int seed, const int min_key_value, const int max_key_value)
{
  srand(seed);
  
  const double delta_key_value = ((double)max_key_value - (double)min_key_value + 0.999) / (double)RAND_MAX;

  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    int new_key = (int)((double)min_key_value + (rand() * delta_key_value));
    assert(new_key <= max_key_value);
    assert(min_key_value <= new_key);
    keys[key_index] = new_key;
  }
}

__attribute__((noinline))
void benchmark_generate_unique_keys(int* keys, const long long int key_count, const int key_value)
{
  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    keys[key_index] = key_value;
  }
}

__attribute__((noinline))
void benchmark_generate_stepping_keys(int* keys, const long long int key_count, const int min_key_value, const int max_key_value)
{
  const double step = ((double)max_key_value - (double)min_key_value + 0.999) / key_count;

  for (long long int key_index = 0; key_index < key_count; ++key_index)
  {
    int new_key = (int)((double)min_key_value + step * (double)key_index);
    keys[key_index] = new_key;
  }
}
