#ifndef LAZY_PRIM_MST_H
#define LAZY_PRIM_MST_H

#include <deque>
#include "Edge_weighted_graph.h"
#include "Queue.h"
#include "Min_pq.h"

class Lazy_prim_mst {
public:
    Lazy_prim_mst(Edge_weighted_graph& G);

    void prim(Edge_weighted_graph& G, int s);

    void scan(Edge_weighted_graph& G, int v);

    std::vector<Edge> edges();

    double weight();

private:
    const static double FLOATING_POINT_EPSILON = std::numeric_limits<double>::epsilon();
    double weight;
    Queue<Edge> mst;
    std::deque<bool> marked;
    Min_pq<Edge> pq;

    bool check(Edge_weighted_graph& G);
};

#endif // LAZY_PRIM_MST_H
