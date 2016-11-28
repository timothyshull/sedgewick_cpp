#include <stdlib.h>
#include "list.h"

link freelist;

void construct(int N) {
    freelist = new node[N + 1];

    for (int i = 0; i < N; i++) {
        freelist[i].next = &freelist[i + 1];
    }
    freelist[N].next = nullptr;
}

Node newNode(int i) {
    link x = remove(freelist);
    x->item = i;
    x->next = x;
    return x;
}

void deleteNode(Node x) {
    insert(freelist, x);
}

void insert(Node x, Node t) {
    t->next = x->next;
    x->next = t;
}

Node remove(Node x) {
    link t = x->next;
    x->next = t->next;
    return t;
}

Node next(Node x) {
    return x->next;
}

Item item(Node x) {
    return x->item;
}
