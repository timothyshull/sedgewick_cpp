#include <fstream>
#include <iostream>

#include "Edge_weighted_digraph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
//    std::ifstream _in{argv[1]};
//    Edge_weighted_digraph g{_in};
    Edge_weighted_digraph g{std::cin};
    Std_out::print_line(g);
    return 0;
}
