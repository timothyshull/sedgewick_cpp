#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <deque>
#include <vector>
#include "Graph.h"

class Connected_component {
public:
    Connected_component(Graph& G);

    int id(int v);

    int size(int v);

    int count();

    bool connected(int v, int w);

    bool areConnected(int v, int w);

private:
    std::deque<bool> marked;
    std::vector<int> id;
    std::vector<int> size;
    int count;

    void dfs(Graph& G, int v);

};

#endif // CONNECTED_COMPONENT_H
