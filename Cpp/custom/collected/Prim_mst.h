#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <limits>
#include <vector>
#include <deque>
#include "Edge.h"
#include "Index_min_pq.h"
#include "Edge_weighted_graph.h"
#include "Queue.h"

class Prim_mst {
public:
    Prim_mst(Edge_weighted_graph& graph);

    Queue<Edge> edges();

    double weight();

private:
    const static double floating_point_epsilon = std::numeric_limits<double>::epsilon();
    std::vector<Edge> _edge_to;
    std::vector<double> _distance_to;
    std::deque<bool> _marked;
    Index_min_pq<double> _pq;

    void _prim(Edge_weighted_graph& graph, int source);

    void _scan(Edge_weighted_graph& graph, int vertex);

    bool _check(Edge_weighted_graph& graph);
};

#endif // PRIM_MST_H
