#pragma once

#include <stddef.h>
#include <stdarg.h>

void string_copy(
    char *destination,
    size_t buffer_size,
    const char *source
);

void string_concat(
    char *destination,
    size_t buffer_size,
    ...
);