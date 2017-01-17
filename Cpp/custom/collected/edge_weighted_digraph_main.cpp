#include <fstream>
#include <iostream>

#include "Edge_weighted_digraph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Edge_weighted_digraph g{std::cin};
    Std_out::print_line(g.to_string());
    return 0;
}
