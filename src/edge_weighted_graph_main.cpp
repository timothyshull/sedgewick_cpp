#include "Std_out.h"
#include "Edge_weighted_graph.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Edge_weighted_graph edge_weighted_graph{in};
    Std_out::print_line(edge_weighted_graph);
    return 0;
}