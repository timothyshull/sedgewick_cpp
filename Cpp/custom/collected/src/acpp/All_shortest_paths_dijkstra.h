// Program 21.4 - Dijkstra's algorithm for all shortest paths
#ifndef ALL_SHORTEST_PATHS_DIJKSTRA_H
#define ALL_SHORTEST_PATHS_DIJKSTRA_H

#include <vector>

#include "Shortest_paths_dijkstra_pfs.h"

template<typename Graph_type, typename Edge_type>
class All_shortest_paths_dijkstra {
public:
    All_shortest_paths_dijkstra(const Graph_type& graph) : _graph{graph}, _all_shortest_paths(graph.num_vertices())
    {
        for (int s{0}; s < graph.num_vertices(); ++s) {
            _all_shortest_paths[s] = new Shortest_paths_dijkstra_pfs<Graph_type, Edge_type>(graph, s);
        }
    }

    Edge_type* path_r(int s, int t) const { return _all_shortest_paths[s]->path_r(t); }

    inline double distance(int s, int t) const { return _all_shortest_paths[s]->dist(t); }

private:
    const Graph_type& _graph;
    std::vector<Shortest_paths_dijkstra_pfs<Graph_type, Edge_type>*> _all_shortest_paths;
};

#endif // ALL_SHORTEST_PATHS_DIJKSTRA_H
