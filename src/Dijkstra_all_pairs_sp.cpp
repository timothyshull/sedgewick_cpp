#include "Dijkstra_all_pairs_sp.h"

Dijkstra_all_pairs_sp::Dijkstra_all_pairs_sp(Edge_weighted_digraph& digraph)
: _all(static_cast<std::vector<Dijkstra_sp>::size_type>(digraph.num_vertices()))
{
    for (auto v = 0; v < digraph.num_vertices(); ++v)
        _all[v] = Dijkstra_sp{digraph, v};
}


