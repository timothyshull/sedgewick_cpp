//#include <algorithm>
#include <iostream>
#include "Doubly_linked_list.h"

int main()
{
    Doubly_linked_list<int> d;

    d.push_back(7);
    d.push_back(5);
    d.push_back(16);
    d.push_back(8);

    try {
        int v = 0;
        for (;;) {
            v = d.pop_back();
            std::cout << v << "\n";
        }
    } catch (...) {
        std::cout << "pop_back on empty list\n";
    }
    return 0;
}