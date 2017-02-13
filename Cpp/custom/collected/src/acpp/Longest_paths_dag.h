// Program 21.6 - Longest paths in an acyclic network
#ifndef LONGEST_PATHS_DAG_H
#define LONGEST_PATHS_DAG_H

#include <vector>

#include "Topological_sort.h"

template<typename Graph_type, typename Edge_type>
class Longest_paths_dag {
public:
    Longest_paths_dag(const Graph_type& graph)
            : _graph{graph},
              _longest_paths(graph.num_vertices()),
              _weights(graph.num_vertices(), 0.0)
    {
        Topological_sort<Graph_type> ts{graph};

        int j;
        int w;
        for (int v = ts[j = 0]; j < graph.V(); v = ts[++j]) {
            typename Graph_type::adjIterator A(graph, v);
            for (Edge_type* e = A.beg(); !A.end(); e = A.nxt()) {
                if (_weights[w = e->w()] < _weights[v] + e->wt()) {
                    _weights[w] = _weights[v] + e->wt();
                    _longest_paths[w] = e;
                }
            }
        }
    }

    Edge_type* pathR(int v) const { return _longest_paths[v]; }

    inline double distance(int v) const { return _weights[v]; }

private:
    const Graph_type& _graph;
    std::vector<double> _weights;
    std::vector<Edge_type*> _longest_paths;
};



#endif // LONGEST_PATHS_DAG_H
