#ifndef EDGE_WEIGHTED_DIRECTED_CYCLE_H
#define EDGE_WEIGHTED_DIRECTED_CYCLE_H

#include <deque>
#include "Edge_weighted_digraph.h"

class Edge_weighted_directed_cycle {
public:
    Edge_weighted_directed_cycle() = default;

    Edge_weighted_directed_cycle(const Edge_weighted_directed_cycle&) = default;

    Edge_weighted_directed_cycle(Edge_weighted_directed_cycle&&) = default;

    ~Edge_weighted_directed_cycle() = default;

    Edge_weighted_directed_cycle& operator=(const Edge_weighted_directed_cycle&) = default;

    Edge_weighted_directed_cycle& operator=(Edge_weighted_directed_cycle&&) = default;

    explicit Edge_weighted_directed_cycle(Edge_weighted_digraph& digraph);

    inline bool has_cycle() const { return !_cycle.is_empty(); }

    inline Stack<Directed_edge> cycle() const { return _cycle; }

private:
    std::deque<bool> _marked;
    std::vector<Directed_edge> _edge_to;
    std::deque<bool> _on_stack;
    Stack<Directed_edge> _cycle;

    void _dfs(Edge_weighted_digraph& digraph, int vertex);

    bool _check(Edge_weighted_digraph& digraph) const;
};

#endif // EDGE_WEIGHTED_DIRECTED_CYCLE_H
