#ifndef NONRECURSIVE_DFS_H
#define NONRECURSIVE_DFS_H

#include <deque>
#include "Graph.h"

class Nonrecursive_dfs {
public:
    Nonrecursive_dfs(Graph& G, int s);
    bool marked(int v);
private:
    std::deque<bool> marked;
};

#endif // NONRECURSIVE_DFS_H
