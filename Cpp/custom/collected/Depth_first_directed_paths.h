#ifndef DEPTH_FIRST_DIRECTED_PATHS_H
#define DEPTH_FIRST_DIRECTED_PATHS_H

#include <vector>
#include <deque>
#include "Digraph.h"
#include "Stack.h"

class Depth_first_directed_paths {
public:
    Depth_first_directed_paths() = delete;

    Depth_first_directed_paths(const Depth_first_directed_paths&) = default;

    Depth_first_directed_paths(Depth_first_directed_paths&&) = default;

    ~Depth_first_directed_paths() = default;

    Depth_first_directed_paths& operator=(const Depth_first_directed_paths&) = default;

    Depth_first_directed_paths& operator=(Depth_first_directed_paths&&) = default;

    Depth_first_directed_paths(Digraph& digraph, int source);

    inline bool has_path_to(int v) const { return _marked[v]; }

    Stack<int> path_to(int vertex) const;

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    const int _source;

    void _dfs(Digraph& digraph, int vertex);
};

#endif // DEPTH_FIRST_DIRECTED_PATHS_H
