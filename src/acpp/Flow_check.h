// Program 22.1 - Flow check and value computation
#ifndef FLOW_CHECK_H
#define FLOW_CHECK_H

namespace Flow_check {
    template<typename Graph_type, typename Edge_type>
    static int flow(Graph_type& graph, int vertex)
    {
        auto x = 0;
        typename Graph_type::adjIterator A(graph, vertex);
        for (auto e : graph.adjacent(vertex)) {
            x += e->from(vertex) ? e->flow() : -e->flow();
        }
        return x;
    }

    template<typename Graph_type>
    static bool flow(Graph_type& graph, int source, int sink)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if ((v != source) && (v != sink)) {
                if (flow(graph, v) != 0) { return false; }
            }
        }
        auto s_flow = flow(graph, source);
        if (s_flow < 0) { return false; }

        return  !(s_flow + flow(graph, sink));
    }
};

#endif // FLOW_CHECK_H
