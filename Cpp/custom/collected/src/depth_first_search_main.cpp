#include "In.h"
#include "Graph.h"
#include "utility.h"
#include "Depth_first_search.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Graph graph{in};
    int s{utility::str_to_num(argv[1])};
    Depth_first_search search{graph, s};
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (search._marked(v)) {
            Std_out::print(v + " ");
        }
    }

    Std_out::print_line();
    if (search._count() != graph.num_vertices()) { Std_out::print_line("NOT connected"); }
    else { Std_out::print_line("connected"); }
    return 0;
}