#include <iostream>

#include "string_search.h"

int main(int argc, char* argv[])
{
    std::string p{argv[1]};
    std::string a;
    a.reserve(a.max_size());

    char t;
    while (std::cin.get(t)) {
        a += t;
    }
    a.shrink_to_fit();

    auto index = string_search(p, a);
    if (index != -1) {
        std::cout << "The string " << p << " occurred at index " << index << "\n";
    } else {
        std::cout << "The string " << p << " was not found\n";
    }
    return 0;

}