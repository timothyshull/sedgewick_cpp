#ifndef ACYCLICLP_H
#define ACYCLICLP_H

#include <type_traits>
#include <vector>

#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Topological.h"

template<class T, class Enable = void>
class Acyclic_lp {};

template<typename Float_type>
class Acyclic_lp<Float_type, typename std::enable_if<std::is_floating_point<Float_type>::value>::type> {
public:
    Acyclic_lp(Edge_weighted_digraph& g, int size) : _distance_to{std::vector<Float_type>(g.num_vertices())}, _edge_to{std::vector<Directed_edge>(g.num_vertices())}
    {
        for (int v = 0; v < g.num_vertices(); v++) {
            _distance_to[v] = std::numeric_limits<Float_type>::infinity();
        }
        _distance_to[size] = 0.0;

        Topological topological{g};

        if (!topological.has_order()) {
            throw std::invalid_argument{"Digraph is not acyclic."};
        }

        for (auto v : topological.order()) {
            for (auto e : g.adjacent(v)) {
                _relax(e);
            }
        }
    }

    inline Float_type distance_to(int v) { return _distance_to[v]; }

    inline bool has_path_to(int v) { return _distance_to[v] < std::numeric_limits<Float_type>::infinity(); }

    Stack<Directed_edge> path_to(int v)
    {
        Stack<Directed_edge> path;
        if (!has_path_to(v)) {
            return path;
        }
        for (Directed_edge e = _edge_to[v];; e = _edge_to[e.from()]) {
            path.push(e);
        }
        return path;
    }

private:
    std::vector<Float_type> _distance_to;
    std::vector<Directed_edge> _edge_to;

    void _relax(Directed_edge& e)
    {
        int v = e.from();
        int w = e.to();
        if (_distance_to[w] < _distance_to[v] + e.weight()) {
            _distance_to[w] = _distance_to[v] + e.weight();
            _edge_to[w] = e;
        }
    }
};

#endif //ACYCLICLP_H
