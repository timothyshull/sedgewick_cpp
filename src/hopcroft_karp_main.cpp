#include "Std_out.h"
#include "Graph_generator.h"
#include "Hopcroft_karp.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    auto v1 = utility::str_to_num(argv[1]);
    auto v2 = utility::str_to_num(argv[2]);
    auto num_edges = utility::str_to_num(argv[3]);
    Graph graph{Graph_generator::bipartite(v1, v2, num_edges)};
    if (graph.num_vertices() < 1000) { Std_out::print_line(graph); }

    Hopcroft_karp matching{graph};

    Std_out::printf("Number of edges _in max matching        = %d\n", matching.size());
    Std_out::printf("Number of vertices _in min vertex cover = %d\n", matching.size());
    Std_out::printf("Graph has a perfect matching           = %d\n", matching.is_perfect());
    Std_out::print_line();

    if (graph.num_vertices() >= 1000) { std::exit(-1); }

    Std_out::print("Max matching: ");
    int w;
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        w = matching.mate(v);
        if (matching.is_matched(v) && v < w) {
            Std_out::print(std::to_string(v) + "-" + std::to_string(w) + " ");
        }
    }
    Std_out::print_line();

    Std_out::print("Min vertex cover: ");
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (matching.in_min_vertex_cover(v)) {
            Std_out::print(v + " ");
        }
    }
    Std_out::print_line();
    return 0;
}