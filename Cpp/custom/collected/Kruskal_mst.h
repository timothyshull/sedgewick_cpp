#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include "Edge_weighted_graph.h"
#include "Queue.h"

class Kruskal_mst {
public:
    Kruskal_mst(Edge_weighted_graph& G);

    std::vector<Edge> edges();

    double weight();

private:
    const static double FLOATING_POINT_EPSILON = std::numeric_limits<double>::epsilon();
    double weight;
    Queue<Edge> mst;

    bool check(Edge_weighted_graph& G);
};

#endif // KRUSKAL_MST_H
