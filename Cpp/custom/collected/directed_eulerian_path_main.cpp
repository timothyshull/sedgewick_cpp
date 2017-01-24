#include "utility.h"

int main(int argc, char *argv[]) {
    int V = utility::safe_convert_integer(argv[1]);
    int E = utility::safe_convert_integer(argv[2]);

    Digraph G1 = Digraph_generator::eulerianCycle(V, E);
    unit_test(G1, "Eulerian cycle");

    Digraph G2 = Digraph_generator::eulerianPath(V, E);
    unit_test(G2, "Eulerian path");

    // add one random edge
    Digraph G3 = new Digraph(G2);
    G3.add_edge(Std_random::uniform(V), Std_random::uniform(V));
    unit_test(G3, "one random edge added to Eulerian path");

    // self loop
    Digraph G4 = new Digraph(V);
    int v4 = Std_random::uniform(V);
    G4.add_edge(v4, v4);
    unit_test(G4, "single self loop");

    // single edge
    Digraph G5 = new Digraph(V);
    G5.add_edge(Std_random::uniform(V), Std_random::uniform(V));
    unit_test(G5, "single edge");

    // empty digraph
    Digraph G6 = new Digraph(V);
    unit_test(G6, "empty digraph");

    // random digraph
    Digraph G7 = Digraph_generator::simple(V, E);
    unit_test(G7, "simple digraph");

    // 4-vertex digraph
    Digraph G8 = new Digraph(new In("eulerianD.txt"));
    unit_test(G8, "4-vertex Eulerian digraph");
    return 0;
}