// Program 19.1 - Reversing a digraph
#ifndef DIGRAPH_REVERSAL_H
#define DIGRAPH_REVERSAL_H

#include "Edge.h"

template<typename In_graph_type, typename Out_graph_type>
void reverse_digraph(const In_graph_type& graph, Out_graph_type& reversed)
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        // typename In_graph_type::adjIterator A(graph, v);
        for (auto w : graph.adjacent(v)) {
            reversed.insert(Edge{w, v});
        }
    }
}


#endif // DIGRAPH_REVERSAL_H
