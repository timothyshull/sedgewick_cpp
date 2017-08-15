#include "utility.h"
#include "Digraph.h"
#include "Std_random.h"
#include "Digraph_generator.h"
#include "In.h"
#include "Directed_eulerian_cycle.h"

int main(int argc, char* argv[])
{
    auto num_vertices = utility::str_to_num(argv[1]);
    auto num_edges = utility::str_to_num(argv[2]);

    Digraph digraph1{Digraph_generator::eulerian_cycle(num_vertices, num_edges)};
    Directed_eulerian_cycle::unit_test(digraph1, "Eulerian _cycle");

    Digraph digraph2{Digraph_generator::eulerian_path(num_vertices, num_edges)};
    Directed_eulerian_cycle::unit_test(digraph2, "Eulerian path");

    Digraph digraph3{num_vertices};
    Directed_eulerian_cycle::unit_test(digraph3, "empty digraph");

    Digraph digraph4{num_vertices};
    auto v4 = Std_random::uniform(num_vertices);
    digraph4.add_edge(v4, v4);
    Directed_eulerian_cycle::unit_test(digraph4, "single self loop");

    Digraph h1{Digraph_generator::eulerian_cycle(num_vertices / 2, num_edges / 2)};
    Digraph h2{Digraph_generator::eulerian_cycle(num_vertices - num_vertices / 2, num_edges - num_edges / 2)};
    std::vector<int> perm;
    perm.reserve(num_vertices);
    for (auto i = 0; i < num_vertices; ++i) {
        perm[i] = i;
    }
    Std_random::shuffle(perm);
    Digraph digraph5{num_vertices};
    for (auto v = 0; v < h1.num_vertices(); ++v) {
        for (int w : h1.adjacent(v)) {
            digraph5.add_edge(perm[v], perm[w]);
        }
    }
    for (auto v = 0; v < h2.num_vertices(); ++v) {
        for (int w : h2.adjacent(v)) {
            digraph5.add_edge(perm[num_vertices / 2 + v], perm[num_vertices / 2 + w]);
        }
    }
    Directed_eulerian_cycle::unit_test(digraph5, "Union of two disjoint cycles");

    Digraph digraph6{Digraph_generator::simple(num_vertices, num_edges)};
    Directed_eulerian_cycle::unit_test(digraph6, "simple digraph");

    Digraph digraph7{In{"eulerianD.txt"}};
    Directed_eulerian_cycle::unit_test(digraph7, "4-vertex Eulerian digraph");
    return 0;
}