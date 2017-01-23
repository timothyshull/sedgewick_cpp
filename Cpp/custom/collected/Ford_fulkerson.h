#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <limits>
#include <vector>
#include <deque>
#include "Flow_edge.h"
#include "Flow_network.h"

class Ford_fulkerson {
public:
    Ford_fulkerson(Flow_network& G, int s, int t);

    double value();

    bool inCut(int v);

private:
    static const double FLOATING_POINT_EPSILON = std::numeric_limits<float>::epsilon();
    std::deque<bool> marked;
    std::vector<Flow_edge> edgeTo;
    double value;

    void validate(int v, int V);

    bool hasAugmentingPath(Flow_network& G, int s, int t);

    double excess(Flow_network& G, int v);

    bool isFeasible(Flow_network& G, int s, int t);

    bool check(Flow_network& G, int s, int t);
};

#endif // FORD_FULKERSON_H
