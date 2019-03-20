#include "benchmark.h"

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
