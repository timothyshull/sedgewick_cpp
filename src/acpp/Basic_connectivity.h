// Program 18.4 - Graph connectivity
#ifndef BASIC_CONNECTIVITY_H
#define BASIC_CONNECTIVITY_H

#include <vector>

template<typename Graph_type>
class Basic_connectivity {
public:
    Basic_connectivity(const Graph_type& graph) : _graph{graph}, _component_count{0}, _id(graph.num_vertices(), -1)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (_id[v] == -1) {
                _connected_component_r(v);
                ++_component_count;
            }
        }
    }

    inline int count() const noexcept { return _component_count; }

    inline bool connected(int s, int t) const { return _id[s] == _id[t]; }

private:
    const Graph_type& _graph;
    int _component_count;
    std::vector<int> _id;

    void _connected_component_r(int w)
    {
        _id[w] = _component_count;
        // typename Graph_type::adjIterator A(_graph, w);
        for (auto v : _graph.adjacent(w)) {
            if (_id[v] == -1) { _connected_component_r(v); }
        }
    }
};

#endif // BASIC_CONNECTIVITY_H
