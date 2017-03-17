// Program 3.13 - List allocation for the Josephus problem
#include <iostream>

#include "free_list.h"

int main(int argc, char* argv[])
{
    int i{std::stoi(argv[1])};
    std::size_t size{std::stoul(argv[1])};
    int skip_size{std::stoi(argv[2])};

    Raw_node_pointer t;
    Raw_node_pointer x;
    construct(size);

    for (i = 2, x = new_node(1); i <= size; ++i) {
        t = new_node(i);
        insert(x, t);
        x = t;
    }

    while (x != next(x)) {
        for (i = 1; i < skip_size; ++i) { x = next(x); }
        delete_node(remove(x));
    }

    std::cout << item(x) << "\n";
    return 0;
}
