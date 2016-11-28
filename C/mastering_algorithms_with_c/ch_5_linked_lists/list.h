#ifndef CH_5_LINKED_LISTS_LIST_H
#define CH_5_LINKED_LISTS_LIST_H

#include <stdlib.h>

typedef struct ListElmt_ {
    void *data;
    struct ListElmt_ *next;
} ListElmt;

typedef struct List_ {
    int size;

    int (*match)(const void *keyl, const void *key2);

    void (*destroy)(void *data);

    ListElmt *head;
    ListElmt *tail;
} List;

void list_init(List *list, void (*destroy)(void *data));

void list_destroy(List *list);

int list_ins_next(List *list, ListElmt *element, const void *data);

int list_rem_next(List *list, ListElmt *element, void **data);

// #define list_size(list) ((list)->size)
int list_size(List *list);

// #define list_head(list) ((list)->head)
ListElmt *list_head(List *list);

// #define list_tail(list) ((list)->tail)
ListElmt *list_tail(List *list);

// #define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
int list_is_head(List *list, ListElmt *element);

// #define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
int list_is_tail(List *list, ListElmt *element);

// #define list_data(element) ((element)->data)
void *list_data(ListElmt *element);

// #define list_next(element) ((element)->next)
ListElmt *list_next(ListElmt *element);

#endif //CH_5_LINKED_LISTS_LIST_H
