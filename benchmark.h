#pragma once

typedef struct benchmark_scope_s benchmark_scope_t;

benchmark_scope_t* benchmark_begin();
int benchmark_end(benchmark_scope_t* scope);
