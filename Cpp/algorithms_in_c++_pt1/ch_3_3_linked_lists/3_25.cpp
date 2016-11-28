struct node {
    int item;
    node *next;
};

void join_circular_lists(node *x, node *t) {
    if (x == nullptr || t == nullptr) {
        return;
    }
    node *tmp = x->next;
    x->next = t->next;
    t->next = tmp;
}