#include "Std_out.h"
#include "Resizing_array_bag.h"

int main(int argc, char* argv[])
{
    Resizing_array_bag<std::string> bag;
    bag.add("Hello");
    bag.add("World");
    bag.add("how");
    bag.add("are");
    bag.add("you");

    for (auto s : bag) {
        Std_out::print_line(s);
    }
    return 0;
}