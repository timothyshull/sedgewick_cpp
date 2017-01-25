#include "In.h"
#include "Edge_weighted_digraph.h"
#include "Std_out.h"
#include "Dijkstra_sp.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Edge_weighted_digraph edge_weighted_digraph{in};
    int s{utility::str_to_num(argv[1])};

    Dijkstra_sp sp{edge_weighted_digraph, s};

    for (int t = 0; t < edge_weighted_digraph.num_vertices(); ++t) {
        if (sp.has_path_to(t)) {
            Std_out::printf("%d to %d (%.2f)  ", s, t, sp.distance_to(t));
            for (Directed_edge e : sp.path_to(t)) {
                Std_out::print(e + "   ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, t);
        }
    }
    return 0;
}