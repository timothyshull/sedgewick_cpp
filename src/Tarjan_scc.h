#ifndef TARJAN_SCC_H
#define TARJAN_SCC_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Tarjan_scc {
public:
    Tarjan_scc() = default;

    Tarjan_scc(const Tarjan_scc&) = default;

    Tarjan_scc(Tarjan_scc&&) = default;

    ~Tarjan_scc() = default;

    Tarjan_scc& operator=(const Tarjan_scc&) = default;

    Tarjan_scc& operator=(Tarjan_scc&&) = default;

    Tarjan_scc(Digraph& digraph);

    inline int count() const noexcept { return _count; }

    inline bool strongly_connected(int v, int w) const { return _id[v] == _id[w]; }

    inline int id(int v) const { return _id[v]; }

private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    std::vector<int> _low;
    int _pre;
    int _count;
    Stack<int> _stack;

    void _dfs(Digraph& digraph, int vertex);

    bool _check(Digraph& digraph);
};

#endif // TARJAN_SCC_H
