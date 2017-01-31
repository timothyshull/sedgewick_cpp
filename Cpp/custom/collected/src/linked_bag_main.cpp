#include <string>
#include "Std_in.h"
#include "Std_out.h"
#include "Linked_bag.h"

int main(int argc, char *argv[]) {
    Linked_bag<std::string> bag{};
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        bag.add(item);
    }

    Std_out::print_line("size of bag = " + bag.size());
    for (auto s : bag) {
        Std_out::print_line(s);
    }
    return 0;
}