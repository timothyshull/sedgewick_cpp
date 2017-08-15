// Program 17.11 - Vertex degrees class implementation
#ifndef VERTEX_DEGREES_H
#define VERTEX_DEGREES_H

#include <vector>

template<typename Graph_type>
class Vertex_degrees {
public:
    Vertex_degrees(const Graph_type& graph) : _graph{graph}, _degree(graph.num_vertices(), 0)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            // typename Graph_type::adjIterator A(graph, v);
            for (auto w : graph.adjacent(v)) {
                _degree[v]++;
            }
        }
    }

    inline int operator[](int v) const { return _degree[v]; }
private:
    const Graph_type& _graph;
    std::vector<int> _degree;
};

#endif // VERTEX_DEGREES_H
