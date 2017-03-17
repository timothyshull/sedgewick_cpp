// Program 17.2 - Example of a graph-processing client
#ifndef GRAPH_CLIENT_EXAMPLE_H
#define GRAPH_CLIENT_EXAMPLE_H

#include <vector>
#include "../Edge.h"

template<typename Graph_type>
std::vector<Edge> edges(Graph_type& graph)
{
    int num_edges{0};
    std::vector<Edge> a(graph.num_edges());
    for (int v{0}; v < graph.num_vertices(); v++) {
        typename Graph_type::adjIterator A(graph, v);
        for (auto w : graph.adjacent(v)) {
            if (graph.directed() || v < w) {
                a[num_edges++] = Edge{v, w};
            }
        }
    }
    return a;
}

#endif // GRAPH_CLIENT_EXAMPLE_H
