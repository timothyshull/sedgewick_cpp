#ifndef CYCLE_H
#define CYCLE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Graph.h"

class Cycle {
public:
    Cycle() = delete;

    Cycle(const Cycle&) = delete;

    Cycle(Cycle&&) = delete;

    ~Cycle() = default;

    Cycle& operator=(const Cycle&) = delete;

    Cycle& operator=(Cycle&&) = delete;

    Cycle(Graph& graph);

    inline bool has_cycle() const { return !_cycle.is_empty(); }

    inline Stack<int> cycle() const { return _cycle; }

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    Stack<int> _cycle;

    bool _has_self_loop(Graph& graph);

    bool _has_parallel_edges(Graph& graph);

    void _dfs(Graph& graph, int u, int v);
};

#endif // CYCLE_H
