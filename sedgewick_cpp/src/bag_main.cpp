#include <iostream>
#include <vector>

#include "Bag.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Bag<std::string> bag;
    std::string item;
    while (!Std_in::is_empty()) {
        item = Std_in::read_string();
        bag.add(item);
    }

    Std_out::print_line("size of bag = " + std::to_string(bag.size()));
    for (auto s : bag) {
        Std_out::print_line(s);
    }

    return 0;
}