#include "Dijkstra_all_pairs_sp.h"

Dijkstra_all_pairs_sp::Dijkstra_all_pairs_sp(Edge_weighted_digraph& G)
{
    all = new DijkstraSP[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v)
        all[v] = new DijkstraSP(G, v);
}

std::vector<Directed_edge> Dijkstra_all_pairs_sp::path(int s, int t)
{
    return all[s].path_to(t);
}

bool Dijkstra_all_pairs_sp::hasPath(int s, int t)
{
    return dist(s, t) < Double.POSITIVE_INFINITY;
}

double Dijkstra_all_pairs_sp::dist(int s, int t)
{
    return all[s].distance_to(t);
}
