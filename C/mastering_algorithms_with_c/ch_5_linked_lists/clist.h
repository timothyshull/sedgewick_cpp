#ifndef CH_5_LINKED_LISTS_CLIST_H
#define CH_5_LINKED_LISTS_CLIST_H

#include <stdlib.h>

typedef struct CListElmt_ {
    void *data;
    struct CListElmt_ *next;
} CListElmt;

typedef struct CList_ {
    int size;

    int (*match)(const void *key1, const void *key2);

    void (*destroy)(void *data);

    CListElmt *head;
} CList;

void clist_init(CList *list, void (*destroy)(void *data));

void clist_destroy(CList *list);

int clist_ins_next(CList *list, CListElmt *element, const void *data);

int clist_rem_next(CList *list, CListElmt *element, void **data);

// #define clist_size(list) ((list)->size)
int clist_size(CList *list);

// #define clist_head(list) ((list)->head)
CListElmt *clist_head(CList *list);

// #define clist_data(element) ((element)->data)
void *clist_data(CListElmt *element);

// #define clist_next(element) ((element)->next)
CListElmt *clist_next(CListElmt *element);

#endif //CH_5_LINKED_LISTS_CLIST_H
