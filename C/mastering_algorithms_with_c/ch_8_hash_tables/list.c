#include "list.h"

void list_init(List *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}

void list_destroy(List *list) {
    void *data;
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    // not necessary
    // memset(list, 0, sizeof(List));
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt *new_element;
    if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL) {
        return -1;
    }

    new_element->data = (void *) data;

    if (element == NULL) {
        if (list_size(list) == 0) {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    } else {
        if (element->next == NULL) {
            list->tail = new_element;
        }

        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;

    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt *old_element;

    if (list_size(list) == 0) {
        return -1;
    }

    if (element == NULL) {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) {
            list->tail = NULL;
        }
    } else {
        if (element->next == NULL) {
            return -1;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;

    return 0;
}

// #define list_size(list) ((list)->size)
int list_size(List *list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}

// #define list_head(list) ((list)->head)
ListElmt *list_head(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}

// #define list_tail(list) ((list)->tail)
ListElmt *list_tail(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->tail;
}

// #define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
int list_is_head(List *list, ListElmt *element) {
    if (list == NULL) {
        return 0;
    } else {
        return element == list->head ? 1 : 0;
    }
}

// #define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
int list_is_tail(List *list, ListElmt *element) {
    if (list == NULL) {
        return 0;
    } else {
        return element == list->tail ? 1 : 0;
    }
}

// #define list_data(element) ((element)->data)
void *list_data(ListElmt *element) {
    if (element == NULL) {
        return NULL;
    }
    return element->data;
}

// #define list_next(element) ((element)->next)
ListElmt *list_next(ListElmt *element) {
    if (element == NULL) {
        return NULL;
    }
    return element->next;
}
