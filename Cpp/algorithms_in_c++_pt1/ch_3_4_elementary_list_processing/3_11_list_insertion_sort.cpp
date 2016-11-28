#include <iostream>
#include <cstdlib>

#include "list.h"

void list_insertion_sort(unsigned int N) {
    node heada(0, nullptr);
    link a = &heada;
    link t = a;

    for (int i = 0; i < N; i++) {
        t = (t->next = new node(rand() % 1000, nullptr));
    }

    node headb(0, nullptr);
    link u;
    link x;
    link b = &headb;

    for (t = a->next; t != 0; t = u) {
        u = t->next;
        for (x = b; x->next != 0; x = x->next) {
            if (x->next->item > t->item) {
                break;
            }
        }
        t->next = x->next;
        x->next = t;
    }
}