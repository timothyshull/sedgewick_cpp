struct node {
    int item;
    node *next;
};

int num_nodes_in_circular_list(node *start) {
    if (start == nullptr) {
        return 0;
    }
    int count = 1;
    node *visitor = start;
    while (start != (visitor = visitor->next)) {
        count++;
    }
    return count;
}