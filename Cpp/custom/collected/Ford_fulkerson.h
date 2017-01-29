#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <limits>
#include <vector>
#include <deque>
#include "Flow_edge.h"
#include "Flow_network.h"

class Ford_fulkerson {
public:
    Ford_fulkerson(Flow_network& network, int source, int dest);

    inline double value() const noexcept { return _value; }

    bool in_cut(int vertex);

private:
    static const double floating_point_epsilon = std::numeric_limits<float>::epsilon();
    std::deque<bool> _marked;
    std::vector<Flow_edge> _edge_to;
    double _value;

    void _validate(int vertex, int num_vertices);

    bool _has_augmenting_path(Flow_network& network, int source, int dest);

    double _excess(Flow_network& network, int vertex);

    bool _is_feasible(Flow_network& network, int source, int dest);

    bool _check(Flow_network& G, int s, int t);
};

#endif // FORD_FULKERSON_H
