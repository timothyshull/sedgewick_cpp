#include "utility.h"
#include "Graph.h"
#include "Graph_generator.h"
#include "Std_random.h"
#include "Eulerian_cycle.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num(argv[1])};
    int num_edges{utility::str_to_num(argv[2])};

    Graph graph1{Graph_generator::eulerian_cycle(num_vertices, num_edges)};
    Eulerian_cycle::unit_test(graph1, "Eulerian cycle");

    Graph graph2{Graph_generator::eulerian_path(num_vertices, num_edges)};
    Eulerian_cycle::unit_test(graph2, "Eulerian path");

    Graph graph3{num_vertices};
    Eulerian_cycle::unit_test(graph3, "empty graph");

    Graph graph4{num_vertices};
    int v4{Std_random::uniform(num_vertices)};
    graph4.add_edge(v4, v4);
    Eulerian_cycle::unit_test(graph4, "single self loop");

    Graph h1{Graph_generator::eulerian_cycle(num_vertices / 2, num_edges / 2)};
    Graph h2{Graph_generator::eulerian_cycle(num_vertices - num_vertices / 2, num_edges - num_edges / 2)};
    std::vector<int> perm;
    perm.reserve(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        perm[i] = i;
    }
    Std_random::shuffle(perm);
    Graph graph5{num_vertices};
    for (int v = 0; v < h1.num_vertices(); ++v) {
        for (int w : h1.adjacent(v)) {
            graph5.add_edge(perm[v], perm[w]);
        }
    }
    for (int v = 0; v < h2.num_vertices(); ++v) {
        for (int w : h2.adjacent(v)) {
            graph5.add_edge(perm[num_vertices / 2 + v], perm[num_vertices / 2 + w]);
        }
    }
    Eulerian_cycle::unit_test(graph5, "Union of two disjoint cycles");

    Graph graph6{Graph_generator::simple(num_vertices, num_edges)};
    Eulerian_cycle::unit_test(graph6, "simple graph");
    return 0;
}