#ifndef CH_6_STACKS_AND_QUEUES_QUEUE_H
#define CH_6_STACKS_AND_QUEUES_QUEUE_H

#include <stdlib.h>

#include "list.h"

typedef List Queue;

#define queue_init list_init

#define queue_destroy list_destroy

int queue_enqueue(Queue *queue, const void *data);

int queue_dequeue(Queue *queue, void **data);

// #define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
void *queue_peek(Queue *queue);

#define queue_size list_size

#endif //CH_6_STACKS_AND_QUEUES_QUEUE_H
