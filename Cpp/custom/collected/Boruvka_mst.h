#ifndef BORUVKA_MST_H
#define BORUVKA_MST_H

#include <limits>
#include <vector>
#include "Edge.h"
#include "Edge_weighted_digraph.h"

class Boruvka_mst {
public:
    Boruvka_mst(Edge_weighted_digraph& G);
    std::vector<Edge> edges();
    double weight();
    bool less(Edge& e, Edge& f);
private:
    const static double FLOATING_POINT_EPSILON = std::numeric_limits<double>::epsilon();
    std::vector<Edge> mst;
    double weight;

    bool check(Edge_weighted_digraph& g);
};

#endif // BORUVKA_MST_H
