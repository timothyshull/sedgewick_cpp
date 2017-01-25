#include "Transitive_closure.h"

Transitive_closure::Transitive_closure(Digraph& G)
{
    tc = new DirectedDFS[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v)
        tc[v] = new DirectedDFS(G, v);
}

bool Transitive_closure::reachable(int v, int w)
{
    return tc[v].marked(w);
}
