#include <stdlib.h>

#include "list.h"
#include "stack.h"

int stack_push(Stack *stack, const void *data) {
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data) {
    return list_rem_next(stack, NULL, data);
}

void *stack_peek(Stack *stack) {
    if (stack == NULL) {
        return NULL;
    }
    return stack->head == NULL ? NULL : stack->head->data;
}