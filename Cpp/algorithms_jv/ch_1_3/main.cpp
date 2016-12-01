#include <iostream>
#include "Linked_list.h"

int main() {
    Linked_list<void>::main();

    Linked_list<std::string> list;
    std::string one{"one"};
    list.insert(one);
    std::string two{"two"};
    list.insert(two);
    std::string three{"three"};
    list.insert(three);
    std::string four{"four"};
    list.insert(four);
    std::string five{"five"};
    list.insert(five);

    for (auto s : list) {
        // this is the node's value
        std::cout << s << "\n";
    }

    std::cout << list.to_string() << "\n";

    return 0;
}