#ifndef KOSARAJU_SHARIR_SCC_H
#define KOSARAJU_SHARIR_SCC_H

#include <deque>
#include <vector>
#include "Digraph.h"

class Kosaraju_sharir_scc {
public:
    Kosaraju_sharir_scc() = default;

    Kosaraju_sharir_scc(const Kosaraju_sharir_scc) = default;

    Kosaraju_sharir_scc(Kosaraju_sharir_scc&&) = default;

    ~Kosaraju_sharir_scc() = default;

    Kosaraju_sharir_scc& operator=(const Kosaraju_sharir_scc) = default;

    Kosaraju_sharir_scc& operator=(Kosaraju_sharir_scc&&) = default;

    Kosaraju_sharir_scc(Digraph& digraph);

    inline int count() const noexcept { return _count; }

    inline bool strongly_connected(int v, int w) const { return _id[v] == _id[w]; }

    inline int id(int v) const { return _id[v]; }

private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    int _count;

    void _dfs(Digraph& digraph, int vertex);

    bool _check(Digraph& digraph);
};

#endif // KOSARAJU_SHARIR_SCC_H
