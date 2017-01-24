#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <limits>
#include <vector>
#include <deque>
#include "Edge.h"
#include "Index_min_pq.h"
#include "Edge_weighted_graph.h"

class Prim_mst {
public:
    Prim_mst(Edge_weighted_graph& G);

    std::vector<Edge> edges();

    double weight();
private:
    const static double FLOATING_POINT_EPSILON = std::numeric_limits<double>::epsilon();
    std::vector<Edge> edgeTo;
    std::vector<double> distTo;
    std::deque<bool> marked;
    Index_min_pq<double> pq;

    void prim(Edge_weighted_graph& G, int s);

    void scan(Edge_weighted_graph& G, int v);

    bool check(Edge_weighted_graph& G);
};

#endif // PRIM_MST_H
