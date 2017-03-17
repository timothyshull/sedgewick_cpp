#ifndef FLOW_NETWORK_H
#define FLOW_NETWORK_H

#include <vector>
#include "Flow_edge.h"
#include "In.h"

class Flow_network {
public:
    Flow_network(int num_vertices);

    Flow_network(int num_vertices, int num_edges);

    Flow_network(In& in);

    inline unsigned long num_vertices() const noexcept { return _num_vertices; }

    inline unsigned long num_edges() const noexcept { return _num_edges; }

    void add_edge(Flow_edge& e);

    void add_edge(int v, int w, double capacity);

    std::vector<Flow_edge> adjacent(int v);

    std::vector<Flow_edge> edges();

    std::string to_string();

private:
    const unsigned long _num_vertices;
    unsigned long _num_edges;
    std::vector<std::vector<Flow_edge>> _adjacency_lists;

    void _validate_vertex(int v);
};

std::ostream& operator<<(std::ostream& os, Flow_network& out);

#endif // FLOW_NETWORK_H
