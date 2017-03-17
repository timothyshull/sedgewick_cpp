#ifndef LAZY_PRIM_MST_H
#define LAZY_PRIM_MST_H

#include <deque>
#include "Edge_weighted_graph.h"
#include "Queue.h"
#include "Min_pq.h"

class Lazy_prim_mst {
public:
    Lazy_prim_mst(Edge_weighted_graph& graph);

    void prim(Edge_weighted_graph& graph, int source);

    void scan(Edge_weighted_graph& graph, int vertex);

    inline Queue<Edge> edges() const { return _mst; }

    inline double weight() const noexcept { return _weight; }

private:
    const static double _floating_point_epsilon = std::numeric_limits<double>::epsilon();
    double _weight;
    Queue<Edge> _mst;
    std::deque<bool> _marked;
    Min_pq<Edge> _pq;

    bool _check(Edge_weighted_graph& graph);
};

#endif // LAZY_PRIM_MST_H
