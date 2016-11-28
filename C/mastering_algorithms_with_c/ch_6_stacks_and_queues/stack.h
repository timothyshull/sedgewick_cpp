#ifndef CH_6_STACKS_AND_QUEUES_STACK_H
#define CH_6_STACKS_AND_QUEUES_STACK_H

#include <stdlib.h>

#include "list.h"

typedef List Stack;

#define stack_init list_init

#define stack_destroy list_destroy

int stack_push(Stack *stack, const void *data);

int stack_pop(Stack *tack, void **data);

// #define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
void *stack_peek(Stack *stack);

#define stack_size list_size

#endif //CH_6_STACKS_AND_QUEUES_STACK_H
