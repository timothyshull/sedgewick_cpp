// Program 21.9 - Bellman-Ford algorithm
#ifndef SHORTEST_PATHS_BELLMAN_FORD_H
#define SHORTEST_PATHS_BELLMAN_FORD_H

#include <vector>
#include <queue>

template<typename Graph_type, typename Edge_type>
class Shortest_paths_bellman_ford {
public:
    Shortest_paths_bellman_ford(Graph_type& graph, int source)
            : _graph{graph},
              _shortest_path(graph.num_vertices()),
              _weights(graph.num_vertices(), graph.num_vertices())
    {
        std::queue<int> queue;
        auto count = 0;
        _weights[source] = 0.0;
        queue.push(source);
        queue.push(graph.num_vertices());
        while (!queue.empty()) {
            int v;
            v = queue.front();
            queue.pop();
            while (v == graph.num_vertices()) {
                if (count++ > graph.V()) { return; }
                queue.push(graph.num_vertices());
                v = queue.front();
                queue.pop();
            }
            // typename Graph_type::adjIterator A(graph, v);
            for (auto e : graph.adjacent(v)) {
                auto w = e->destination();
                double p = _weights[v] + e->weight();
                if (p < _weights[w]) {
                    _weights[w] = p;
                    queue.push(w);
                    _shortest_path[w] = e;
                }
            }
        }
    }

    inline Edge_type* path_r(int v) const { return _shortest_path[v]; }

    inline double distance(int v) const { return _weights[v]; }

private:
    const Graph_type& _graph;
    std::vector<double> _weights;
    std::vector<Edge_type*> _shortest_path;
};

#endif // SHORTEST_PATHS_BELLMAN_FORD_H
