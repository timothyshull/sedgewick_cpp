#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include <vector>
#include "Index_min_pq.h"
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"

class Dijkstra_sp {
public:
    Dijkstra_sp(Edge_weighted_digraph&G, int s);
    double distTo(int v);
    bool hasPathTo(int v);
    std::vector<Directed_edge> pathTo(int v);
private:
    std::vector<double> distTo;
    std::vector<Directed_edge> edgeTo;
    Index_min_pq<double> pq;

    void relax(Directed_edge& e);
    bool check(Edge_weighted_digraph& G, int s);
};

#endif // DIJKSTRA_SP_H
