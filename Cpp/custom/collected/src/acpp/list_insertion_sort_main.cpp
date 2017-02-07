// Program 3.11 - List insertion sort
#include <cstddef>
#include <string>
#include <random>
#include <iostream>

#include "free_list.h"

int main(int argc, char* argv[])
{
    std::size_t n{std::stoul(argv[1])};
    Node head_a{0, nullptr};
    Raw_node_pointer a{&head_a};
    Raw_node_pointer t{a};

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> uniform_dist{0, 999};

    for (int i = 0; i < n; ++i) {
        t->next = new Node{uniform_dist(gen), nullptr};
        t = t->next;
    }

    list_insertion_sort(head_a.next);
    t = head_a.next;
    while (t != nullptr) {
        std::cout << t->item << " ";
    }
    std::cout << "\n";

    return 0;
}