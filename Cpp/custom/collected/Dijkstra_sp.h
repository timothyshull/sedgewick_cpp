#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include <vector>
#include "Index_min_pq.h"
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"

class Dijkstra_sp {
public:
    Dijkstra_sp(Edge_weighted_digraph& digraph, int source);

    inline double distance_to(int vertex) const { return _distance_to[vertex]; }

    inline bool has_path_to(int v) const { return _distance_to[v] < std::numeric_limits<double>::infinity(); }

    Stack<Directed_edge> path_to(int vertex);

private:
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;
    Index_min_pq<double> _pq;

    void _relax(Directed_edge& edge);

    bool _check(Edge_weighted_digraph& digraph, int source);
};

#endif // DIJKSTRA_SP_H
