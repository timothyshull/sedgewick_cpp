#include "Graph.h"
#include "utility.h"
#include "Std_random.h"
#include "Graph_generator.h"
#include "Eulerian_path.h"

int main(int argc, char* argv[])
{
    int num_vertices{utility::str_to_num(argv[1])};
    int num_edges{utility::str_to_num(argv[2])};

    Graph graph1{Graph_generator::eulerian_cycle(num_vertices, num_edges)};
    Eulerian_path::unit_test(graph1, "Eulerian _cycle");

    Graph graph2{Graph_generator::eulerian_path(num_vertices, num_edges)};
    Eulerian_path::unit_test(graph2, "Eulerian path");

    Graph graph3{graph2};
    graph3.add_edge(Std_random::uniform(num_vertices), Std_random::uniform(num_vertices));
    Eulerian_path::unit_test(graph3, "one random edge added to Eulerian path");

    Graph graph4{num_vertices};
    int v4{Std_random::uniform(num_vertices)};
    graph4.add_edge(v4, v4);
    Eulerian_path::unit_test(graph4, "single self loop");

    Graph graph5{num_vertices};
    graph5.add_edge(Std_random::uniform(num_vertices), Std_random::uniform(num_vertices));
    Eulerian_path::unit_test(graph5, "single edge");

    Graph graph6{num_vertices};
    Eulerian_path::unit_test(graph6, "empty graph");

    Graph graph7{Graph_generator::simple(num_vertices, num_edges)};
    Eulerian_path::unit_test(graph7, "simple graph");
    return 0;
}