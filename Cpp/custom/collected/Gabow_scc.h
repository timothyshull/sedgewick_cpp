#ifndef GABOW_SCC_H
#define GABOW_SCC_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Gabow_scc {
public:
    Gabow_scc(Digraph& G);

    int count();

    bool stronglyCOnnected(int v, int w);

    int id(int v);

private:
    std::deque<bool> marked;
    std::vector<int> id;
    std::vector<int> preorder;
    int pre;
    int count;
    Stack<int> stack1;
    Stack<int> stack2;

    void dfs(Digraph& G, int v);

    bool check(Digraph& G);
};

#endif // GABOW_SCC_H
