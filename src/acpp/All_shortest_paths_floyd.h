// Program 21.5 - Floyd's algorithm for all shortest paths
#ifndef ALL_SHORTEST_PATHS_FLOYD_H
#define ALL_SHORTEST_PATHS_FLOYD_H

#include <vector>

template<typename Graph_type, typename Edge_type>
class All_shortest_paths_floyd {
public:
    All_shortest_paths_floyd(const Graph_type& graph)
            : _graph{graph},
              _paths(graph.num_vertices()),
              _distances(graph.num_vertices())
    {
        auto num_vertices = graph.num_vertices();
        for (int i{0}; i < num_vertices; ++i) {
            _paths[i].assign(num_vertices, 0);
            _distances[i].assign(num_vertices, num_vertices);
        }
        for (int s{0}; s < num_vertices; ++s) {
            for (int t{0}; t < num_vertices; ++t) {
                if (graph.edge(s, t)) {
                    _paths[s][t] = graph.edge(s, t);
                    _distances[s][t] = graph.edge(s, t)->weight();
                }
            }
        }
        for (int s{0}; s < num_vertices; ++s) { _distances[s][s] = 0; }
        for (int i{0}; i < num_vertices; ++i) {
            for (int s{0}; s < num_vertices; ++s) {
                if (_paths[s][i]) {
                    for (int t = 0; t < num_vertices; ++t) {
                        if (s != t) {
                            if (_distances[s][t] > _distances[s][i] + _distances[i][t]) {
                                _paths[s][t] = _paths[s][i];
                                _distances[s][t] = _distances[s][i] + _distances[i][t];
                            }
                        }
                    }
                }
            }
        }
    }

    inline Edge_type* path(int s, int t) const { return _paths[s][t]; }

    inline double distance(int s, int t) const { return _distances[s][t]; }

private:
    const Graph_type& _graph;
    std::vector<std::vector<Edge_type*>> _paths;
    std::vector<std::vector<double>> _distances;
};

#endif // ALL_SHORTEST_PATHS_FLOYD_H
