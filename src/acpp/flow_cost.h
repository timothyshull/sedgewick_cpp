// Program 22.8 - Computing flow cost
#ifndef FLOW_COST_H
#define FLOW_COST_H

template<typename Graph_type>
static int cost(Graph_type& graph)
{
    auto x = 0;
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        // typename Graph_type::adjIterator A(graph, v);
        for (auto e : graph.adjacent(v)) {
            if (e->from(v) && e->cost_r_to(e->destination()) < C) {
                x += e->flow() * e->cost_r_to(e->destination());
            }
        }
    }
    return x;
}

#endif // FLOW_COST_H
