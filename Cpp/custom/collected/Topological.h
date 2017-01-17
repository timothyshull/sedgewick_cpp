#ifndef TOPOLOGICAL_H
#define TOPOLOGICAL_H

#include <vector>
#include "Digraph.h"
#include "Edge_weighted_digraph.h"

class Topological {
public:
    Topological() = default;

    Topological(const Topological&) = default;

    Topological(Topological&&) = default;

    ~Topological() = default;

    Topological& operator=(const Topological&) = default;

    Topological& operator=(Topological&&) = default;

    explicit Topological(Digraph& g);

    explicit Topological(Edge_weighted_digraph& g);

    inline std::vector<int> order() const { return _order; }

    inline bool has_order() const { return !_order.empty(); }

    int rank(int v) const;

private:
    std::vector<int> _order;
    std::vector<int> _rank;

    void _validate_vertex(int v) const;
};

#endif //TOPOLOGICAL_H
