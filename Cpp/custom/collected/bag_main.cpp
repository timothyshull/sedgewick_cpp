#include <iostream>
#include <vector>

#include "Bag.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Bag<std::string> bag;
    std::vector<std::string> vs = Std_in::read_all_strings();
    for (auto s : vs) {
        bag.add(s);
    }

    Std_out::printf("The size of the bag is: %d", bag.size());
    for (auto s : bag) {
        Std_out::print_line(s);
    }

    // Std_out::print_line(bag);

    return 0;
}