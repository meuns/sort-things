#include "benchmark.h"

#include <time.h>

typedef struct benchmark_scope_s
{
  struct timespec start_time;
  struct timespec end_time;
}
benchmark_scope_t;

static benchmark_scope_t benchmark_ring_buffer[64];
static const int benchmark_ring_size = sizeof(benchmark_ring_buffer) / sizeof(benchmark_ring_buffer[0]);
static int benchmark_ring_head = 0;

__attribute__((always_inline))
benchmark_scope_t* benchmark_begin()
{
  benchmark_scope_t* new_scope = &benchmark_ring_buffer[benchmark_ring_head];
  benchmark_ring_head = (benchmark_ring_head + 1) % benchmark_ring_size;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &new_scope->start_time);

  return new_scope;
}

__attribute__((always_inline))
int benchmark_end(benchmark_scope_t* scope)
{
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &scope->end_time);
  long long duration_ns = (scope->end_time.tv_sec - scope->start_time.tv_sec) * 1000000000LL + (scope->end_time.tv_nsec - scope->start_time.tv_nsec);
  long long duration_ms = duration_ns / 1000000L;
  return (int)duration_ms;
}
