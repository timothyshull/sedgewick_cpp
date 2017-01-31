#include "utility.h"
#include "Graph.h"
#include "Graph_generator.h"
#include "Std_random.h"
#include "Std_out.h"
#include "Bipartite_x.h"

int main(int argc, char* argv[])
{
    int v1{utility::str_to_num<int>(argv[1])};
    int v2{utility::str_to_num<int>(argv[2])};
    int e{utility::str_to_num<int>(argv[3])};
    int f{utility::str_to_num<int>(argv[4])};

    Graph graph{Graph_generator::bipartite(v1, v2, e)};

    for (int i{0}; i < f; ++i) {
        int v = Std_random::uniform(v1 + v2);
        int w = Std_random::uniform(v1 + v2);
        graph.add_edge(v, w);
    }

    Std_out::print_line(graph);

    Bipartite_x b{graph};
    if (b.is_bipartite()) {
        Std_out::print_line("Graph is bipartite");
        for (int v{0}; v < graph.num_vertices(); ++v) {
            Std_out::print_line(v + ": " + static_cast<bool>(b.color(v)));
        }
    } else {
        Std_out::print("Graph has an odd-length cycle: ");
        for (int x : b.odd_cycle()) {
            Std_out::print(x + " ");
        }
        Std_out::print_line();
    }
    return 0;
}