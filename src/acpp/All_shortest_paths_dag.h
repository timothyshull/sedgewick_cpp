// Program 21.7 - All shortest paths in an acyclic network
#ifndef ALL_SHORTEST_PATHS_DAG_H
#define ALL_SHORTEST_PATHS_DAG_H

#include <vector>

template<typename Graph_type, typename Edge_type>
class All_shortest_paths_dag {
public:
    All_shortest_paths_dag(const Graph_type& graph)
            : _graph{graph},
              _paths(graph.num_vertices()),
              _distances(graph.num_vertices())
    {
        auto num_vertices = graph.num_vertices();
        for (auto i = 0; i < num_vertices; ++i) {
            _paths[i].assign(num_vertices, nullptr);
            _distances[i].assign(num_vertices, num_vertices);
        }
        for (auto s = 0; s < num_vertices; ++s) {
            if (_paths[s][s] == nullptr) { _dfs_r(s); }
        }
    }

    inline Edge_type* path(int s, int t) const { return _paths[s][t]; }

    inline double distance(int s, int t) const { return _distances[s][t]; }

private:
    const Graph_type& _graph;
    std::vector<std::vector<Edge_type*>> _paths;
    std::vector<std::vector<double>> _distances;

    void _dfs_r(int s)
    {
        // typename Graph_type::adjIterator A(_graph, s);
        for (auto e : _graph.adjacent(s)) {
            auto t = e->dest();
            double w{e->weight()};
            if (_distances[s][t] > w) {
                _distances[s][t] = w;
                _paths[s][t] = e;
            }
            if (_paths[t][t] == nullptr) { _dfs_r(t); }
            for (auto i = 0; i < _graph.num_vertices(); ++i) {
                if (_paths[t][i]) {
                    if (_distances[s][i] > w + _distances[t][i]) {
                        _distances[s][i] = w + _distances[t][i];
                        _paths[s][i] = e;
                    }
                }
            }
        }
    }
};

#endif // ALL_SHORTEST_PATHS_DAG_H
