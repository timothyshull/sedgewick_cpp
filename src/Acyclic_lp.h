#ifndef ACYCLIC_LP_H
#define ACYCLIC_LP_H

#include <type_traits>
#include <vector>

#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Topological.h"

class Acyclic_lp {
private:
    static const Directed_edge _default = Directed_edge{};
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;

public:
    Acyclic_lp() = default;

    Acyclic_lp(const Acyclic_lp&) = default;

    Acyclic_lp(Acyclic_lp&&) = default;

    ~Acyclic_lp() = default;

    Acyclic_lp& operator=(const Acyclic_lp&) = default;

    Acyclic_lp& operator=(Acyclic_lp&&) = default;

    Acyclic_lp(Edge_weighted_digraph& digraph, int source);

    inline double distance_to(int v) const { return _distance_to[v]; }

    inline bool has_path_to(int v) const { return _distance_to[v] > -std::numeric_limits<double>::infinity(); }

    Stack<Directed_edge> path_to(int vertex);

private:
    void _relax(Directed_edge& e);

};

#endif // ACYCLIC_LP_H
