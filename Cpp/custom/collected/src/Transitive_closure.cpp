#include "Transitive_closure.h"

Transitive_closure::Transitive_closure(Digraph& digraph)
        : _tc{static_cast<std::vector<Directed_dfs>::size_type>(digraph.num_vertices())}
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        _tc.emplace_back(digraph, v);
    }
}
