#include "Transitive_closure.h"

Transitive_closure::Transitive_closure(Digraph& digraph)
        : _tc(digraph.num_vertices())
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        _tc.emplace_back(digraph, v);
    }
}
