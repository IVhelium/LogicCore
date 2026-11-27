#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "console/input.h"

bool input_read_line(char *buffer, size_t buffer_size)
{
    if (buffer == NULL) return false;
    if (!fgets(buffer, buffer_size, stdin)) return false;

    int len = 0;
    while (buffer[len] != '\0') len++;

    if (len > 0 && buffer[len - 1] != '\n') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return false;
    }

    if (len > 0) buffer[len - 1] = '\0';

    return true;
}

bool input_limit_check(int value, int min, int max, RangeMode mode)
{
    if (min > max) return false;

    bool min_ok = (mode == RANGE_CLOSED || mode == RANGE_LEFT_CLOSED)
        ? (min <= value) : (min < value);

    bool max_ok = (mode == RANGE_CLOSED || mode == RANGE_RIGHT_CLOSED)
        ? (value <= max) : (value < max);

    return min_ok && max_ok;
}

bool input_read_int(int *value)
{
    char buffer[CONSOLE_INPUT_SIZE];
    if (!input_read_line(buffer, sizeof(buffer))) return false;    

    char *endPtr;
    long result = strtol(buffer, &endPtr, 10);

    if (result > INT_MAX || result < INT_MIN) return false;
    if (endPtr == buffer || *endPtr != '\0') return false;

    *value = (int)result;

    return true;
}

bool input_read_int_range(int *value, int min, int max, RangeMode mode)
{   
    int temp_value;
    
    if (value == NULL) return false;
    if (!input_read_int(&temp_value)) return false;
    if (!input_limit_check(temp_value, min, max, mode)) return false;

    *value = temp_value;

    return true;
}

bool input_read_string(char *destination, size_t destination_size)
{
    if (!input_read_line(destination, destination_size)) return false;

    return true;
}