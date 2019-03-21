#pragma once

typedef struct benchmark_scope_s benchmark_scope_t;

benchmark_scope_t* benchmark_begin(void);
int benchmark_end_ms(benchmark_scope_t* scope);
int benchmark_end_us(benchmark_scope_t* scope);
int benchmark_end_ns(benchmark_scope_t* scope);

void benchmark_generate_random_keys(int* keys, const long long int key_count, const unsigned int seed, const int min_key_value, const int max_key_value);
void benchmark_generate_unique_keys(int* keys, const long long int key_count, const int key_value);
void benchmark_generate_stepping_keys(int* keys, const long long int key_count, const int min_key_value, const int max_key_value);
