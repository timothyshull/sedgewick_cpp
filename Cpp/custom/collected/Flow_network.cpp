#include "Flow_network.h"

Flow_network::Flow_network(int V)
{
    if (V < 0) throw new IllegalArgumentException("Number of vertices in a Graph must be nonnegative");
    this.V = V;
    this.E = 0;
    adj = (Bag<FlowEdge>[]) new Bag[V];
    for (int v = 0; v < V; v++)
        adj[v] = new Bag<FlowEdge>();
}

Flow_network::Flow_network(int V, int E)
{
    this(V);
    if (E < 0) throw new IllegalArgumentException("Number of edges must be nonnegative");
    for (int i = 0; i < E; i++) {
        int v = StdRandom.uniform(V);
        int w = StdRandom.uniform(V);
        double capacity = StdRandom.uniform(100);
        addEdge(new FlowEdge(v, w, capacity));
    }
}

Flow_network::Flow_network(In& in)
{
    this(in.readInt());
    int E = in.readInt();
    if (E < 0) throw new IllegalArgumentException("Number of edges must be nonnegative");
    for (int i = 0; i < E; i++) {
        int v = in.readInt();
        int w = in.readInt();
        if (v < 0 || v >= V)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
        if (w < 0 || w >= V)
            throw new IndexOutOfBoundsException("vertex " + w + " is not between 0 and " + (V - 1));
        double capacity = in.readDouble();
        addEdge(new FlowEdge(v, w, capacity));
    }
}

int Flow_network::V()
{
    return V;
}

int Flow_network::E()
{
    return E;
}

void Flow_network::addEdge(Flow_edge& e)
{
    int v = e.from();
    int w = e.to();
    validateVertex(v);
    validateVertex(w);
    adj[v].add(e);
    adj[w].add(e);
    E++;
}

std::vector<Flow_edge> Flow_network::adj(int v)
{
    validateVertex(v);
    return adj[v];
}

std::vector<Flow_edge> Flow_network::edges()
{
    Bag<FlowEdge> list = new Bag<FlowEdge>();
    for (int v = 0; v < V; v++)
        for (FlowEdge e : adj(v)) {
            if (e.to() != v)
                list.add(e);
        }
    return list;
}

std::string Flow_network::toString()
{
    StringBuilder s = new StringBuilder();
    s.append(V + " " + E + NEWLINE);
    for (int v = 0; v < V; v++) {
        s.append(v + ":  ");
        for (FlowEdge e : adj[v]) {
            if (e.to() != v) s.append(e + "  ");
        }
        s.append(NEWLINE);
    }
    return s.toString();
}

void Flow_network::validateVertex(int v)
{
    if (v < 0 || v >= V)
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
}

std::ostream& operator<<(std::ostream& os, Flow_network& out)
{
    return os << out.toString();
}
