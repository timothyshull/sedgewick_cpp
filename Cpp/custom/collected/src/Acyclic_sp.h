#ifndef ACYCLIC_SP_H
#define ACYCLIC_SP_H

#include <vector>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"

class Acyclic_sp {
public:
    Acyclic_sp() = default;

    Acyclic_sp(const Acyclic_sp&) = default;

    Acyclic_sp(Acyclic_sp&&) = default;

    ~Acyclic_sp() = default;

    Acyclic_sp& operator=(const Acyclic_sp&) = default;

    Acyclic_sp& operator=(Acyclic_sp&&) = default;

    Acyclic_sp(Edge_weighted_digraph& g, int source);

    inline double distance_to(int v) const { return _distance_to[v]; }

    inline bool has_path_to(int v) const { return _distance_to[v] < std::numeric_limits<double>::infinity(); }

    std::vector<Directed_edge> path_to(int vertex);

private:
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;

    void _relax(Directed_edge& e);
};

#endif // ACYCLIC_SP_H
