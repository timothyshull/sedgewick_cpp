#ifndef DIRECTED_CYCLE_H
#define DIRECTED_CYCLE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Directed_cycle {
public:
    Directed_cycle() = default;

    Directed_cycle(const Directed_cycle&) = default;

    Directed_cycle(Directed_cycle&&) = default;

    ~Directed_cycle() = default;

    Directed_cycle& operator=(const Directed_cycle&) = default;

    Directed_cycle& operator=(Directed_cycle&&) = default;

    explicit Directed_cycle(Digraph& g);

    inline bool has_cycle() const { return !_cycle.is_empty(); }

    Stack<int> cycle() const;

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::deque<bool> _on_stack;
    Stack<int> _cycle;

    void _dfs(Digraph& g, int v);

    bool _check() const;
};

#endif //DIRECTED_CYCLE_H
