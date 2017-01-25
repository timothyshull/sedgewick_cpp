#include "Std_out.h"
#include "Directed_edge.h"
#include "Std_random.h"
#include "Adj_matrix_edge_weighted_digraph.h"
#include "Floyd_warshall.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num<int>(argv[1])};
    int num_edges{utility::str_to_num<int>(argv[2])};
    Adj_matrix_edge_weighted_digraph digraph{num_vertices};

    for (int i{0}; i < num_edges; ++i) {
        int v{Std_random::uniform(num_vertices)};
        int w{Std_random::uniform(num_vertices)};
        double weight{std::round(100 * (Std_random::uniform() - 0.15)) / 100.0};
        if (v == w) {
            digraph.add_edge(v, w, std::abs(weight));
        } else {
            digraph.add_edge(v, w, weight);
        }
    }

    Std_out::print_line(digraph);

    Floyd_warshall spt{digraph};

    Std_out::printf("  ");
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        Std_out::printf("%6d ", v);
    }
    Std_out::print_line();

    for (int v{0}; v < digraph.num_vertices(); ++v) {
        Std_out::printf("%3d: ", v);
        for (int w{0}; w < digraph.num_vertices(); ++w) {
            if (spt.has_path(v, w)) {
                Std_out::printf("%6.2f ", spt.distance(v, w));
            } else {
                Std_out::printf("  Inf ");
            }
        }
        Std_out::print_line();
    }

    if (spt.has_negative_cycle()) {
        Std_out::print_line("Negative _cost _cycle:");
        for (Directed_edge e : spt.negative_cycle()) {
            Std_out::print_line(e);
        }
        Std_out::print_line();
    } else {
        for (int v{0}; v < digraph.num_vertices(); ++v) {
            for (int w{0}; w < digraph.num_vertices(); ++w) {
                if (spt.has_path(v, w)) {
                    Std_out::printf("%d to %d (%5.2f)  ", v, w, spt.distance(v, w));
                    for (Directed_edge e : spt.path(v, w)) {
                        Std_out::print(e + "  ");
                    }
                    Std_out::print_line();
                } else {
                    Std_out::printf("%d to %d no path\n", v, w);
                }
            }
        }
    }
    return 0;
}