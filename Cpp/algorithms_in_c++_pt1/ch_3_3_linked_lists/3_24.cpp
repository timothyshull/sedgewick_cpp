struct node {
    int item;
    node *next;
};

int num_nodes_between(node *x, node *t) {
    if (x == t || x == nullptr || t == nullptr) {
        return 0;
    }
    int count = 1;
    node *visitor = x;
    while (t != (visitor = visitor->next)) {
        count++;
    }
    return count;
}