#include "utility.h"
#include "Graph.h"
#include "Graph_generator.h"
#include "Std_random.h"
#include "Std_out.h"
#include "Bipartite.h"

int main(int argc, char *argv[]) {
    int v1 = utility::safe_convert_integer(argv[1]);
    int v2 = utility::safe_convert_integer(argv[2]);
    int e = utility::safe_convert_integer(argv[3]);
    int f = utility::safe_convert_integer(argv[4]);

    Graph g = Graph_generator::bipartite(v1, v2, e);
    for (int i = 0; i < f; ++i) {
        int v = Std_random::uniform(v1 + v2);
        int w = Std_random::uniform(v1 + v2);
        g.add_edge(v, w);
    }

    Std_out::print_line(g);

    Bipartite b{g};
    if (b.is_bipartite()) {
        Std_out::print_line("Graph is bipartite");
        for (int v = 0; v < g.num_vertices(); ++v) {
            Std_out::print_line(v + ": " + b.color(v));
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