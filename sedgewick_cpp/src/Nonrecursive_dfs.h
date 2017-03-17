#ifndef NONRECURSIVE_DFS_H
#define NONRECURSIVE_DFS_H

#include <deque>
#include "Graph.h"

class Nonrecursive_dfs {
public:
    Nonrecursive_dfs(Graph& graph, int source);

    ~Nonrecursive_dfs() = default;

    inline bool marked(int v) const { return _marked[v]; }

private:
    std::deque<bool> _marked;
};

#endif // NONRECURSIVE_DFS_H
