#include "utility.h"
#include "Digraph.h"
#include "Std_random.h"
#include "Digraph_generator.h"
#include "In.h"
#include "Directed_eulerian_cycle.h"

int main(int argc, char* argv[])
{
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);

    Digraph G1{Digraph_generator::eulerian_cycle(V, E)};
    Directed_eulerian_cycle::unit_test(G1, "Eulerian cycle");

    Digraph G2{Digraph_generator::eulerian_path(V, E)};
    Directed_eulerian_cycle::unit_test(G2, "Eulerian path");

    Digraph G3{V};
    Directed_eulerian_cycle::unit_test(G3, "empty digraph");

    Digraph G4{V};
    int v4{Std_random::uniform(V)};
    G4.add_edge(v4, v4);
    Directed_eulerian_cycle::unit_test(G4, "single self loop");

    Digraph H1 = Digraph_generator::eulerian_cycle(V / 2, E / 2);
    Digraph H2 = Digraph_generator::eulerian_cycle(V - V / 2, E - E / 2);
    std::vector<int> perm;
    perm.reserve(V);
    for (int i = 0; i < V; ++i) {
        perm[i] = i;
    }
    Std_random::shuffle(perm);
    Digraph G5{V};
    for (int v = 0; v < H1.num_vertices(); ++v) {
        for (int w : H1.adj(v)) {
            G5.add_edge(perm[v], perm[w]);
        }
    }
    for (int v = 0; v < H2.num_vertices(); ++v) {
        for (int w : H2.adj(v)) {
            G5.add_edge(perm[V / 2 + v], perm[V / 2 + w]);
        }
    }
    Directed_eulerian_cycle::unit_test(G5, "Union of two disjoint cycles");

    Digraph G6 = Digraph_generator::simple(V, E);
    Directed_eulerian_cycle::unit_test(G6, "simple digraph");

    Digraph G7 = new Digraph(new In("eulerianD.txt"));
    Directed_eulerian_cycle::unit_test(G7, "4-vertex Eulerian digraph");
    return 0;
}