#include "utility.h"
#include "Digraph.h"
#include "Digraph_generator.h"
#include "Std_random.h"
#include "Directed_eulerian_path.h"
#include "In.h"

int main(int argc, char* argv[])
{
    auto num_vertices = utility::str_to_num(argv[1]);
    auto num_edges = utility::str_to_num(argv[2]);

    Digraph digraph1{Digraph_generator::eulerian_cycle(num_vertices, num_edges)};
    Directed_eulerian_path::unit_test(digraph1, "Eulerian _cycle");

    Digraph digraph2{Digraph_generator::eulerian_path(num_vertices, num_edges)};
    Directed_eulerian_path::unit_test(digraph2, "Eulerian path");

    Digraph digraph3{digraph2};
    digraph3.add_edge(Std_random::uniform(num_vertices), Std_random::uniform(num_vertices));
    Directed_eulerian_path::unit_test(digraph3, "one random edge added to Eulerian path");

    Digraph graph4{num_vertices};
    auto v4 = Std_random::uniform(num_vertices);
    graph4.add_edge(v4, v4);
    Directed_eulerian_path::unit_test(graph4, "single self loop");

    Digraph digraph5{num_vertices};
    digraph5.add_edge(Std_random::uniform(num_vertices), Std_random::uniform(num_vertices));
    Directed_eulerian_path::unit_test(digraph5, "single edge");

    Digraph digraph6{num_vertices};
    Directed_eulerian_path::unit_test(digraph6, "empty digraph");

    Digraph digraph7{Digraph_generator::simple(num_vertices, num_edges)};
    Directed_eulerian_path::unit_test(digraph7, "simple digraph");

    Digraph digraph8{In{"eulerianD.txt"}};
    Directed_eulerian_path::unit_test(digraph8, "4-vertex Eulerian digraph");
    return 0;
}