#ifndef NONRECURSIVE_DIRECTED_DFS_H
#define NONRECURSIVE_DIRECTED_DFS_H

#include <deque>
#include "Digraph.h"

class Nonrecursive_directed_dfs {
public:
    Nonrecursive_directed_dfs(Digraph& digraph, int source);

    ~Nonrecursive_directed_dfs() = default;

    inline bool marked(int v) const { return _marked[v]; }

private:
    std::deque<bool> _marked;
};

#endif // NONRECURSIVE_DIRECTED_DFS_H
