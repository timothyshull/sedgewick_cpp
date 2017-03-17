// Program 3.10 - List reversal
// Program 3.11 - List insertion sort
// Program 3.12 - List processing interface
// Program 3.14 - Implementation of list-processing interface
#ifndef FREE_LIST_H
#define FREE_LIST_H

#include <vector>

struct Node;

using Item_type = int;

using Owning_node_pointer = Node*;

using Raw_node_pointer = Node*;

struct Node {
    Node() : item{}, next{nullptr} {}

    Node(Item_type x, Raw_node_pointer t) : item{x}, next{t} {}

    inline ~Node() { if (next) { delete next; }};

    Item_type item;
    Owning_node_pointer next;
};

void construct(std::size_t size);

Raw_node_pointer new_node(Item_type item);

void delete_node(Raw_node_pointer x);

void insert(Raw_node_pointer x, Raw_node_pointer t);

Raw_node_pointer remove(Raw_node_pointer x);

inline Raw_node_pointer next(Raw_node_pointer x) { return x ? x->next : nullptr; }

inline Item_type item(Raw_node_pointer x) { return x ? x->item : std::numeric_limits<int>::min(); } // a means to check for bad return val

Raw_node_pointer reverse(Raw_node_pointer x);

void list_insertion_sort(Raw_node_pointer a);

#endif // FREE_LIST_H
