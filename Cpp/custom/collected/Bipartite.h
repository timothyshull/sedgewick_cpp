#ifndef BIPARTITE_H
#define BIPARTITE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Graph.h"

class Bipartite {
public:
    Bipartite(Graph& G);
    bool is_bipartite();
    bool color(int v);
    std::vector<int> odd_cycle();
private:
    bool is_bipartite;
    std::deque<bool> color;
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    Stack<int> cycle;

    void dfs(Graph& G, int v);
    bool check(Graph& G);
};

#endif // BIPARTITE_H
