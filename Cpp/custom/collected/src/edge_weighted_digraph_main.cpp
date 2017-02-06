#include "Edge_weighted_digraph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Edge_weighted_digraph graph{in};
    Std_out::print_line(graph);
    return 0;
}
