#ifndef DIRECTED_DFS_H
#define DIRECTED_DFS_H

#include <deque>
#include "Digraph.h"

class Directed_dfs {
public:
    Directed_dfs(Digraph& digraph, int source);

    Directed_dfs(Digraph& digraph, std::vector<int>& sources);

    inline bool marked(int v) const { return _marked[v]; }

    inline int count() const noexcept { return _count; }

private:
    std::deque<bool> _marked;
    int _count;

    void _dfs(Digraph& digraph, int vertex);
};

#endif // DIRECTED_DFS_H
