#ifndef BIPARTITE_H
#define BIPARTITE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Graph.h"

class Bipartite {
public:
    Bipartite(Graph& G);
    bool isBipartite();
    bool color(int v);
    std::vector<int> oddCycle();
private:
    bool isBipartite;
    std::deque<bool> color;
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    Stack<int> cycle;

    void dfs(Graph& G, int v);
    bool check(Graph& G);
};

#endif // BIPARTITE_H
