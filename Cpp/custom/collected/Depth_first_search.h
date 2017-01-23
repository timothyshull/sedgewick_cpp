#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <deque>
#include "Graph.h"

class Depth_first_search {
public:
    Depth_first_search(Graph& G, int s);
    bool marked(int v);
    int count();
private:
    std::deque<bool> marked;
    int count;

    void dfs(Graph& G, int v);
};

#endif // DEPTH_FIRST_SEARCH_H
