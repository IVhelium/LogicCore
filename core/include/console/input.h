#pragma once

#include <stddef.h>

constexpr int CONSOLE_INPUT_SIZE = 256;

typedef enum RangeMode {
    RANGE_CLOSED,         // [min, max] -> min <= x <= max
    RANGE_OPEN,           // (min, max) -> min <  x <  max
    RANGE_LEFT_CLOSED,    // [min, max) -> min <= x <  max
    RANGE_RIGHT_CLOSED    // (min, max] -> min <  x <= max
} RangeMode;


bool input_read_line(char* buffer, size_t buffer_size);
bool input_limit_check(int value, int min, int max, RangeMode mode);
bool input_read_int(int *value);
bool input_read_int_range(int *value, int min, int max, RangeMode mode);
bool input_read_string(char *destination, size_t destination_size);