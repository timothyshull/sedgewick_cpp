#ifndef GABOW_SCC_H
#define GABOW_SCC_H

#include <deque>
#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Gabow_scc {
public:
    Gabow_scc(Digraph& G);

    inline int count() const noexcept { return _count; }

    inline bool strongly_connected(int source, int dest) const { return _id[source] == _id[dest]; }

    inline int id(int vertex) const { return _id[vertex]; }

private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    std::vector<int> _preorder;
    int _pre;
    int _count;
    Stack<int> _stack1;
    Stack<int> _stack2;

    void _dfs(Digraph& G, int v);

    bool _check(Digraph& digraph);
};

#endif // GABOW_SCC_H
