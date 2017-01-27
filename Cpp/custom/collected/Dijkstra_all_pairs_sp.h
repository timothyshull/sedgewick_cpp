#ifndef DIJKSTRA_ALL_PAIRS_SP_H
#define DIJKSTRA_ALL_PAIRS_SP_H

#include "Edge_weighted_digraph.h"
#include "Dijkstra_sp.h"

class Dijkstra_all_pairs_sp {
public:
    Dijkstra_all_pairs_sp(Edge_weighted_digraph& digraph);

    inline std::vector<Directed_edge> path(int s, int t) const { return _all[s].path_to(t); }

    inline bool has_path(int source, int dest) const { return distance(source, dest) < std::numeric_limits<double>::infinity(); }

    inline double distance(int source, int dest) const { return _all[source]._distance_to(dest); }

private:
    std::vector<Dijkstra_sp> _all;

};

#endif // DIJKSTRA_ALL_PAIRS_SP_H
