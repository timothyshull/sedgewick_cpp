#ifndef ACYCLIC_SP_H
#define ACYCLIC_SP_H

#include <vector>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"

class Acyclic_sp {
private:
    static const Directed_edge _default;
    std::vector<double> _distance_to;
    std::vector<Directed_edge> _edge_to;

public:
    Acyclic_sp() = default;

    Acyclic_sp(const Acyclic_sp&) = default;

    Acyclic_sp(Acyclic_sp&&) = default;

    ~Acyclic_sp() = default;

    Acyclic_sp& operator=(const Acyclic_sp&) = default;

    Acyclic_sp& operator=(Acyclic_sp&&) = default;

    Acyclic_sp(Edge_weighted_digraph& digraph, int source);

    inline double distance_to(int vertex) const { return _distance_to[vertex]; }

    inline bool has_path_to(int vertex) const { return _distance_to[vertex] > -std::numeric_limits<double>::infinity(); }

    Stack<Directed_edge> path_to(int vertex);

private:
    void _relax(Directed_edge& edge);

};

#endif // ACYCLIC_SP_H
