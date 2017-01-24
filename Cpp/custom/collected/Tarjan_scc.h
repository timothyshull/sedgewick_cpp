#ifndef TARJAN_SCC_H
#define TARJAN_SCC_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Tarjan_scc {
public:
    Tarjan_scc(Digraph& G);

    int count();

    bool stronglyConnected(int v, int w);

    int id(int v);

private:
    std::deque<bool> marked;
    std::vector<int> id;
    std::vector<int> low;
    int pre;
    int count;
    Stack<int> stack;

    void dfs(Digraph& G, int v);

    bool check(Digraph& G);
};

#endif // TARJAN_SCC_H
