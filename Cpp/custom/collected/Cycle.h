#ifndef CYCLE_H
#define CYCLE_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Graph.h"

class Cycle {
public:
    Cycle(Graph& G);
    bool hasCycle();
    std::vector<int> cycle();
private:
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    Stack<int> cycle;

    bool hasSelfLoop(Graph& G);
    bool hasParallelEdges(Graph& G);
    void dfs(Graph& G, int u, int v);
};

#endif // CYCLE_H
