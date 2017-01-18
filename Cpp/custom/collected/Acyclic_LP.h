#ifndef ACYCLICLP_H
#define ACYCLICLP_H

#include <type_traits>
#include <vector>

#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Topological.h"

class Acyclic_lp {
public:
    Acyclic_lp() = default;

    Acyclic_lp(const Acyclic_lp&) = default;

    Acyclic_lp(Acyclic_lp&&) = default;

    ~Acyclic_lp() = default;

    Acyclic_lp& operator=(const Acyclic_lp&) = default;

    Acyclic_lp& operator=(Acyclic_lp&&) = default;

    Acyclic_lp(Edge_weighted_digraph& g, int source);

    inline double distance_to(int v) const { return _distance_to[v]; }

    inline bool has_path_to(int v) const { return _distance_to[v] < std::numeric_limits<double>::infinity(); }

    Stack<Directed_edge> path_to(int v);

private:
    std::vector<double> _distance_to;
    std::vector<Directed_edge*> _edge_to;

    void _relax(Directed_edge& e);
};

#endif //ACYCLICLP_H
