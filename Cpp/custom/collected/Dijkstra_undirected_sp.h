#ifndef DIJKSTRA_UNDIRECTED_SP_H
#define DIJKSTRA_UNDIRECTED_SP_H

#include "Edge_weighted_digraph.h"
#include "Index_min_pq.h"

class Dijkstra_undirected_sp {
public:
    Dijkstra_undirected_sp(Edge_weighted_digraph&G, int s);
    double distance_to(int v);
    bool has_path_to(int v);
    std::vector<Directed_edge> path_to(int v);
private:
    std::vector<double> distance_to;
    std::vector<Directed_edge> edgeTo;
    Index_min_pq<double> pq;

    void relax(Directed_edge& e);
    bool check(Edge_weighted_digraph& G, int s);
};

#endif // DIJKSTRA_UNDIRECTED_SP_H
