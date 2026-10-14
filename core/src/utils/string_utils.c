#include "utils/string_utils.h"

void string_copy(char *destination, size_t buffer_size, const char *source)
{
    if (buffer_size == 0) return;   // Защита от нулевого размера буфера

    size_t i = 0;

    while (source[i] != '\0' && i < buffer_size - 1)
    {
        destination[i] = source[i];
        i++;
    }
    
    destination[i] = '\0';
}

void string_concat_impl(char *destination, size_t buffer_size, ...)
{
    va_list list;                   // Создаем лист принимаемых аргументов "..."

    if (buffer_size == 0) return;
    if (destination == NULL) return;

    va_start(list, buffer_size);    // Инициализация аргументов

    destination[0] = '\0';
    size_t i = 0;
    const char *current_string = va_arg(list, const char *);

    while (current_string != NULL)   // Цыкл длится пока не встретит аргумент NULL
    {
        size_t j = 0;
        
        while (current_string[j] != '\0' && i < buffer_size - 1)
        {
            destination[i] = current_string[j];

            i++;
            j++;
        }

        current_string = va_arg(list, const char *);
    }

    destination[i] = '\0';

    va_end(list);
}