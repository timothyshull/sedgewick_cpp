#ifndef DIRECTED_DFS_H
#define DIRECTED_DFS_H

#include <deque>
#include "Digraph.h"

class Directed_dfs {
public:
    Directed_dfs(Digraph& G, int s);

    Directed_dfs(Digraph& G, std::vector<int>& sources);

    bool marked(int v);

    int count();

private:
    std::deque<bool> marked;
    int count;

    void dfs(Digraph& G, int v);
};

#endif // DIRECTED_DFS_H
