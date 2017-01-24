#ifndef NONRECURSIVE_DIRECTED_DFS_H
#define NONRECURSIVE_DIRECTED_DFS_H

#include <deque>
#include "Digraph.h"

class Nonrecursive_directed_dfs {
public:
    Nonrecursive_directed_dfs(Digraph& G, int s);
    bool marked(int v);
private:
    std::deque<bool> marked;
};

#endif // NONRECURSIVE_DIRECTED_DFS_H
