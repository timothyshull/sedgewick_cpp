#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <deque>
#include <vector>
#include "Graph.h"

class Connected_component {
public:
    Connected_component() = default;

    Connected_component(const Connected_component&) = default;

    Connected_component(Connected_component&&) = default;

    ~Connected_component() = default;

    Connected_component& operator=(const Connected_component&) = default;

    Connected_component& operator=(Connected_component&&) = default;

    Connected_component(Graph& graph);

    inline int id(int v) const { return _id[v]; }

    inline int size(int v) const { return _size[_id[v]]; }

    inline int count() const noexcept { return _count; }

    inline bool connected(int v, int w) const { return _id(v) == _id(w); }

    inline bool are_connected(int v, int w) const { return _id(v) == _id(w); }

private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    std::vector<int> _size;
    int _count;

    void _dfs(Graph& G, int v);

};

#endif // CONNECTED_COMPONENT_H
