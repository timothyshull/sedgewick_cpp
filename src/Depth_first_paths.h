#ifndef DEPTH_FIRST_PATHS_H
#define DEPTH_FIRST_PATHS_H

#include <vector>
#include <deque>

#include "Digraph.h"
#include "Stack.h"

class Depth_first_paths {
public:
    Depth_first_paths() = delete;

    Depth_first_paths(const Depth_first_paths&) = default;

    Depth_first_paths(Depth_first_paths&&) = default;

    ~Depth_first_paths() = default;

    Depth_first_paths& operator=(const Depth_first_paths&) = default;

    Depth_first_paths& operator=(Depth_first_paths&&) = default;

    Depth_first_paths(Digraph& digraph, int source);

    bool has_path_to(int v);

    inline bool Depth_first_paths::has_path_to(int v) const { return _marked[v]; }

    Stack<int> path_to(int v);

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    const int _source;

    void _dfs(Digraph& G, int v);

};

#endif // DEPTH_FIRST_PATHS_H
