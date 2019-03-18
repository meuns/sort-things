#include "test.h"

#include <stdlib.h>
#undef max
#undef min

#define KEY_TYPE int
#define CONCAT_SUFFIX(name) name##_int
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE

#define KEY_TYPE signed char
#define CONCAT_SUFFIX(name) name##_char
#include "test_template.c"
#undef CONCAT_SUFFIX
#undef KEY_TYPE
