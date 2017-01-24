#ifndef DEPTH_FIRST_PATHS_H
#define DEPTH_FIRST_PATHS_H

#include <vector>
#include <deque>
#include "Digraph.h"

class Depth_first_paths {
public:
    Depth_first_paths(Digraph& G, int s);

    bool has_path_to(int v);

    std::vector<int> path_to(int v);

private:
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    const int s;

    void dfs(Digraph& G, int v);

};

#endif // DEPTH_FIRST_PATHS_H
