#pragma once

#include <stddef.h>
#include <stdarg.h>

void string_copy(
    char *destination,
    size_t buffer_size,
    const char *source
);

char *string_concat_impl(
    char *destination,
    size_t buffer_size,
    ...
);

#define string_concat(destination, buffer_size, ...) string_concat_impl(destination, buffer_size, __VA_ARGS__, (const char *)NULL)