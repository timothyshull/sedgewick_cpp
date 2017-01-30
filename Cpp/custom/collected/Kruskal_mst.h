#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include "Edge_weighted_graph.h"
#include "Queue.h"

class Kruskal_mst {
public:
    Kruskal_mst(Edge_weighted_graph& graph);

    inline Queue<Edge> edges() const { return _mst; }

    inline double weight() const noexcept { return _weight; }

private:
    const static double _floating_point_epsilon = std::numeric_limits<double>::epsilon();
    double _weight;
    Queue<Edge> _mst;

    bool _check(Edge_weighted_graph& graph);
};

#endif // KRUSKAL_MST_H
