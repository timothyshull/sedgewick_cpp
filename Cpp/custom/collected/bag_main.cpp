#include<iostream>

#include "Bag.h"

int main() {
    Bag<std::string> bag;

    for (std::string line; std::getline(std::cin, line) && line != "";) {
        bag.add(line);
    }
    std::cout << "The size of the bag is: " << bag.size() << "\n";

    for (auto s : bag) {
        std::cout << s << "\n";
    }

    return 0;
}