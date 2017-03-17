// Program 4.10 - Equivalence relations ADT client
#include <iostream>
#include "Union_find.h"

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    Union_find info{size};

    int p;
    int q;
    while (std::cin >> p >> q) {
        if (!info.find(p, q)) {
            info.unite(p, q);
            std::cout << " " << p << " " << q << "\n";
        }
    }

    return 0;
}

