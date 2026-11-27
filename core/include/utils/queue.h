#pragma once

typedef struct IntQueue {
    int *items;
    int capacity;
    int count;
    int head;
    int tail;
} IntQueue;


void queue_destroy(IntQueue *queue);

bool queue_init(IntQueue *queue, int capacity);
bool queue_pop(IntQueue *queue, int *value);
bool queue_push(IntQueue *queue, int value);
bool queue_is_empty(const IntQueue *queue);
bool queue_is_full(const IntQueue *queue);