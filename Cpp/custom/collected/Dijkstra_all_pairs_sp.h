#ifndef DIJKSTRA_ALL_PAIRS_SP_H
#define DIJKSTRA_ALL_PAIRS_SP_H

#include "Edge_weighted_digraph.h"
#include "Dijkstra_sp.h"

class Dijkstra_all_pairs_sp {
public:
    Dijkstra_all_pairs_sp(Edge_weighted_digraph& G);
    std::vector<Directed_edge> path(int s, int t);
    bool hasPath(int s, int t);
    double dist(int s, int t);
private:
    std::vector<Dijkstra_sp> all;

};

#endif // DIJKSTRA_ALL_PAIRS_SP_H
