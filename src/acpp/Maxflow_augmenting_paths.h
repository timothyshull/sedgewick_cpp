// Program 22.3 - Augmenting-paths maxflow implementation
#ifndef MAXFLOW_AUGMENTING_PATHS_H
#define MAXFLOW_AUGMENTING_PATHS_H

#include <vector>

#include "Priority_queue_prim_pfs.h"

template<typename Graph, typename Edge> 
class Maxflow_augmenting_paths {
public:
    Maxflow_augmenting_paths(const Graph& graph, int source, int sink) 
            : _graph{graph}, 
              _source(source), 
              _sink(sink), 
              _search_tree(graph.num_vertices()), 
              _weights(graph.num_vertices()) { while (_pfs()) { augment(source, sink); }}

private:
    const Graph& _graph;
    int _source;
    int _sink;
    std::vector<int> _weights;
    std::vector<Edge*> _search_tree;

    inline int _resolve_st(int v) const { return _search_tree[v]->other(v); }
    
    void augment(int s, int t)
    {
        int d{_search_tree[t]->cap_r_to(t)};
        for (int v{_resolve_st(t)}; v != s; v = _resolve_st(v)) {
            if (_search_tree[v]->cap_r_to(v) < d) {
                d = _search_tree[v]->cap_r_to(v);
            }
        }
        _search_tree[t]->add_flow_r_to(t, d);
        for (int v{_resolve_st(t)}; v != s; v = _resolve_st(v)) {
            _search_tree[v]->add_flow_r_to(v, d);
        }
    }

    bool _pfs()
    {
        Priority_queue_prim_pfs<int> priority_queue{_graph.num_vertices(), _weights};
        for (int v{0}; v < _graph.num_vertices(); ++v) {
            _weights[v] = 0;
            _search_tree[v] = 0;
            priority_queue.insert(v);
        }
        _weights[_source] = std::numeric_limits<int>::min();
        priority_queue.lower(_source);
        while (!priority_queue.empty()) {
            int v{priority_queue.get_min()};
            _weights[v] = std::numeric_limits<int>::min();
            if (v == _sink || (v != _source && _search_tree[v] == 0)) { break; }
            // typename Graph::adjIterator A(_graph, v);
            for (auto e : _graph.adjacent(v)) {
                int w{e->other(v)};
                int cap{e->cap_r_to(w)};
                int p{cap < -_weights[v] ? cap : -_weights[v]};
                if (cap > 0 && -p < _weights[w]) {
                    _weights[w] = -p;
                    priority_queue.lower(w);
                    _search_tree[w] = e;
                }
            }
        }
        return _search_tree[_sink] != 0;
    }
};



#endif // MAXFLOW_AUGMENTING_PATHS_H
