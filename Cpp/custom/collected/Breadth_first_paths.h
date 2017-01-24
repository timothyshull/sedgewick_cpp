#ifndef BREADTH_FIRST_PATHS_H
#define BREADTH_FIRST_PATHS_H

#include <vector>
#include <deque>
#include "Graph.h"

class Breadth_first_paths {
public:
    Breadth_first_paths(Graph& G, int s);
    Breadth_first_paths(Graph& G, std::vector<int>& sources);
    bool has_path_to(int v);
    int distance_to(int v);
    std::vector<int> path_to(int v);
private:
    const static int INFINITY = std::numeric_limits<int>::max();
    std::deque<bool> marked;
    std::vector<int> edgeTo;
    std::vector<int> distance_to;

    void bfs(Graph& G, int s);
    void bfs(Graph& G, std::vector<int>& sources);
    bool check(Graph& G, int s);

};

#endif // BREADTH_FIRST_PATHS_H
