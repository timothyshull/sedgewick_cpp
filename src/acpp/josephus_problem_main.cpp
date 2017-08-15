// Program 3.9 - Circular list example (Josephus problem)
#include <iostream>

#include "free_list.h"

int main(int argc, char* argv[])
{
    auto n = std::stoi(argv[1]);
    auto m = std::stoi(argv[2]);
    Raw_node_pointer t{new Node{1, nullptr}};
    t->next = t;
    Raw_node_pointer x{t};

    int i;
    for (i = 2; i <= n; ++i) {
        x->next = new Node{i, t};
        x = x->next;
    }

    // has memory leaks, not necessary to clean up
    while (x != x->next) {
        for (i = 1; i < m; ++i) { x = x->next; }
        x->next = x->next->next;
    }
    std::cout << x->item << "\n";
    return 0;
}