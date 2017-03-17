#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <deque>
#include "Graph.h"

class Depth_first_search {
public:
    Depth_first_search(Graph& graph, int source);

    inline bool marked(int vertex) const { return _marked[vertex]; }

    inline int count() const noexcept { return _count; }

private:
    std::deque<bool> _marked;
    int _count;

    void _dfs(Graph& G, int v);
};

#endif // DEPTH_FIRST_SEARCH_H
