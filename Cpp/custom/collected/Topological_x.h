#ifndef TOPOLOGICAL_X_H
#define TOPOLOGICAL_X_H

#include <vector>
#include "Queue.h"
#include "Digraph.h"
#include "Edge_weighted_digraph.h"

class Topological_x {
public:
    Topological_x(Digraph& digraph);

    Topological_x(Edge_weighted_digraph& digraph);

    inline Queue<int> order() const { return _order; }

    inline bool has_order() const { return !_order.is_empty(); }

    int rank(int v);

private:
    Queue<int> _order;
    std::vector<int> _rank;

    bool _check(Digraph& digraph);

    bool _check(Edge_weighted_digraph& digraph);

    void _validate_vertex(int v);
};

#endif // TOPOLOGICAL_X_H
