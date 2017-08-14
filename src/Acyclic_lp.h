#ifndef ACYCLIC_LP_H
#define ACYCLIC_LP_H

#include <type_traits>
#include <vector>

#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Topological.h"

class Acyclic_lp {
public:
    Acyclic_lp() = default;

    Acyclic_lp(const Acyclic_lp &) = default;

    Acyclic_lp(Acyclic_lp &&) = default;

    ~Acyclic_lp() = default;

    Acyclic_lp &operator=(const Acyclic_lp &) = default;

    Acyclic_lp &operator=(Acyclic_lp &&) = default;

    Acyclic_lp(Edge_weighted_digraph &digraph, int source);

    double distance_to(int v) const
    {
        return _distance_to[v];
    }

    bool has_path_to(int v) const
    {
        return -std::numeric_limits<double>::infinity() < _distance_to[v];
    }

    Stack<Directed_edge> path_to(int vertex);

private:
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;

    void _relax(Directed_edge const &e);

    Directed_edge _default()
    {
        static const auto default_edge = Directed_edge{};
        return default_edge;
    }
};

#endif // ACYCLIC_LP_H
