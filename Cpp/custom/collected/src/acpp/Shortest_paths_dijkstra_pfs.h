// Program 21.1 - Dijkstra's algorithm (priority-first search)
#ifndef SHORTEST_PATH_DIJKSTRA_PFS_H
#define SHORTEST_PATH_DIJKSTRA_PFS_H

#include <vector>
#include <queue>

#include "Priority_queue_prim_pfs.h"

template<typename Graph, typename Edge> class Shortest_paths_dijkstra_pfs {
public:
    Shortest_paths_dijkstra_pfs(const Graph& graph, int source)
            : _graph{graph},
              _shortest_path(graph.num_vertices(), nullptr),
              _weights(graph.num_vertices(), graph.num_vertices())
    {
        Priority_queue_prim_pfs<double> priority_queue(graph.num_vertices(), _weights);
        for (int v{0}; v < graph.num_vertices(); ++v) { priority_queue.insert(v); }
        _weights[source] = 0.0;
        priority_queue.lower(source);
        int v;
        while (!priority_queue.empty()) {
            v = priority_queue.get_min(); // wt[v] = 0.0;
            if (v != source && _shortest_path[v] == 0) { return; }
            // typename Graph::adjIterator A(graph, v);
            for (auto e : graph.adjacent(v)) {
                int w{e->destination()};
                double p = _weights[v] + e->weight();
                if (p < _weights[w]) {
                    _weights[w] = p;
                    priority_queue.lower(w);
                    _shortest_path[w] = e;
                }
            }
        }
    }

    Edge* path_r(int v) const { return _shortest_path[v]; }

    double distance(int v) const { return _weights[v]; }

private:
    const Graph& _graph;
    std::vector<double> _weights;
    std::vector<Edge*> _shortest_path;
};

#endif // SHORTEST_PATH_DIJKSTRA_PFS_H
