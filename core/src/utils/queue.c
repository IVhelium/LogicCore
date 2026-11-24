#include <stdlib.h>
#include <stddef.h>
#include "utils/queue.h"

void queue_destroy(IntQueue *queue)
{
    if (queue == NULL) return;

    free(queue->items);

    queue->items = NULL;
    queue->capacity = 0;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;
}

bool queue_init(IntQueue *queue, int capacity)
{
    if (queue == NULL) return false;
    if (capacity <= 0) return false;

    queue->items = malloc(capacity * sizeof(*queue->items));    // Задаем размер массиву элементов через динамическое выделение памяти

    if (queue->items == NULL) return false;

    queue->capacity = capacity;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;

    return true;
}

bool queue_pop(IntQueue *queue, int *value)
{
    if (queue == NULL) return false;
    if (queue_is_empty(queue)) return false;

    *value = queue->items[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;

    return true;
}

bool queue_push(IntQueue *queue, int value)
{
    if (queue == NULL) return false;
    if (queue_is_full(queue)) return false;

    queue->items[queue->tail] = value;
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count++;

    return true;
}

bool queue_is_empty(const IntQueue *queue)
{
    if (queue == NULL) return false;

    return queue->count == 0;
}

bool queue_is_full(const IntQueue *queue)
{
    if (queue == NULL) return false;

    return queue->count == queue->capacity;
}