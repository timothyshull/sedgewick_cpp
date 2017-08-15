#include "In.h"
#include "Edge_weighted_graph.h"
#include "utility.h"
#include "Dijkstra_undirected_sp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Edge_weighted_graph edge_weighted_graph{in};
    int s = utility::str_to_num(argv[1]);

    Dijkstra_undirected_sp sp{edge_weighted_graph, s};

    for (auto t = 0; t < edge_weighted_graph.num_vertices(); ++t) {
        if (sp.has_path_to(t)) {
            Std_out::printf("%d to %d (%.2f)  ", s, t, sp._distance_to(t));
            for (auto e : sp.path_to(t)) {
                Std_out::print(e + "   ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, t);
        }
    }
    return 0;
}