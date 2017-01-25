#include "Flow_network.h"

Flow_network::Flow_network(int V)
{
    if (V < 0) throw utility::Illegal_argument_exception("Number of vertices in a Graph must be nonnegative");
    this.V = V;
    this.E = 0;
    adj = (Bag<FlowEdge>[]) new Bag[V];
    for (int v{0}; v < V; ++v)
        adj[v] = new Bag<FlowEdge>();
}

Flow_network::Flow_network(int V, int E)
{
    this(V);
    if (E < 0) throw utility::Illegal_argument_exception("Number of edges must be nonnegative");
    for (int i{0}; i < E; ++i) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        double capacity = Std_random::uniform(100);
        add_edge(new FlowEdge(v, w, capacity));
    }
}

Flow_network::Flow_network(In& in)
{
    this(in.read_int());
    int E = in.read_int();
    if (E < 0) throw utility::Illegal_argument_exception("Number of edges must be nonnegative");
    for (int i{0}; i < E; ++i) {
        int v = in.read_int();
        int w = in.read_int();
        if (v < 0 || v >= V)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
        if (w < 0 || w >= V)
            throw new IndexOutOfBoundsException("vertex " + w + " is not between 0 and " + (V - 1));
        double capacity = in.read_double();
        add_edge(new FlowEdge(v, w, capacity));
    }
}

int Flow_network::num_vertices()
{
    return V;
}

int Flow_network::num_edges()
{
    return E;
}

void Flow_network::add_edge(Flow_edge& e)
{
    int v = e.from();
    int w = e.to();
    validateVertex(v);
    validateVertex(w);
    adj[v].add(e);
    adj[w].add(e);
    ++E;
}

std::vector<Flow_edge> Flow_network::adj(int v)
{
    validateVertex(v);
    return adj[v];
}

std::vector<Flow_edge> Flow_network::edges()
{
    Bag<FlowEdge> list = new Bag<FlowEdge>();
    for (int v{0}; v < V; ++v)
        for (FlowEdge e : adjacent(v)) {
            if (e.to() != v)
                list.add(e);
        }
    return list;
}

std::string Flow_network::to_string()
{
    std::stringstream s = new std::stringstream();
    s.append(V + " " + E + NEWLINE);
    for (int v{0}; v < V; ++v) {
        s.append(v + ":  ");
        for (FlowEdge e : adj[v]) {
            if (e.to() != v) s.append(e + "  ");
        }
        s.append(NEWLINE);
    }
    return s.to_string();
}

void Flow_network::validateVertex(int v)
{
    if (v < 0 || v >= V)
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
}

std::ostream& operator<<(std::ostream& os, Flow_network& out)
{
    return os << out.to_string();
}
