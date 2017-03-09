#ifndef TOPOLOGICAL_H
#define TOPOLOGICAL_H

#include <vector>
#include "Digraph.h"
#include "Edge_weighted_digraph.h"

class Topological {
private:
    Stack<int> _order;
    std::vector<int> _rank;

public:
    Topological() = default;

    Topological(const Topological&) = default;

    Topological(Topological&&) = default;

    ~Topological() = default;

    Topological& operator=(const Topological&) = default;

    Topological& operator=(Topological&&) = default;

    explicit Topological(Digraph& g);

    explicit Topological(Edge_weighted_digraph& g);

    inline Stack<int> order() const { return _order; }

    inline bool has_order() const { return !_order.is_empty(); }

    int rank(int v) const;

private:
    void _validate_vertex(int v) const;

};

#endif // TOPOLOGICAL_H
