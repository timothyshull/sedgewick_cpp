// Program 3.10 - List reversal
// Program 3.11 - List insertion sort
// Program 3.12 - List processing interface
// Program 3.14 - Implementation of list-processing interface
#include "free_list.h"

std::vector<Node> free_list; // element 0 is a dummy head

void construct(std::size_t size)
{
    free_list.clear();
    free_list.reserve(size + 1);
    for (int i{0}; i < size; ++i) {
        free_list[i].next = &free_list[i + 1];
    }
    free_list[size].next = nullptr;
}

Raw_node_pointer new_node(Item_type item)
{
    Raw_node_pointer x{remove(&free_list[0])};
    x->item = item;
    x->next = x; // self-loop
    return x;
}

void delete_node(Raw_node_pointer x) { insert(&free_list[0], x); }

void insert(Raw_node_pointer x, Raw_node_pointer t)
{
    t->next = x->next;
    x->next = t;
}

Raw_node_pointer remove(Raw_node_pointer x)
{
    Raw_node_pointer t{x->next};
    x->next = t->next;
    return t;
}

Raw_node_pointer reverse(Raw_node_pointer x)
{
    Raw_node_pointer t;
    Raw_node_pointer y{x};
    Raw_node_pointer r{nullptr};
    while (y != nullptr) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }
    return r;
}

void list_insertion_sort(Raw_node_pointer a)
{
    Node dummy;
    Raw_node_pointer t;
    Raw_node_pointer u;
    Raw_node_pointer x;
    Raw_node_pointer b{&dummy};

    for (t = a; t != nullptr; t = u) {
        u = t->next;
        for (x = b; x->next != nullptr; x = x->next) {
            if (x->next->item > t->item) { break; }
        }
        t->next = x->next;
        x->next = t;
    }
}
