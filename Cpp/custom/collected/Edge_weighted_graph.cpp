#include "Edge_weighted_graph.h"

Edge_weighted_graph::Edge_weighted_graph(int V)
{
    if (V < 0) { throw utility::Illegal_argument_exception("Number of vertices must be nonnegative"); }
    this.V = V;
    this.E = 0;
    adj = (Bag<Edge>[])
    new Bag[V];
    for (int v = 0; v < V; ++v) {
        adj[v] = new Bag<Edge>();
    }
}

Edge_weighted_graph::Edge_weighted_graph(int V, int E)
{
    this(V);
    if (E < 0) { throw utility::Illegal_argument_exception("Number of edges must be nonnegative"); }
    for (int i = 0; i < E; ++i) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        double weight = std::round(100 * Std_random::uniform()) / 100.0;
        Edge e = new Edge(v, w, weight);
        add_edge(e);
    }
}

Edge_weighted_graph::Edge_weighted_graph(In& in)
{
    this(in.read_int());
    int E = in.read_int();
    if (E < 0) { throw utility::Illegal_argument_exception("Number of edges must be nonnegative"); }
    for (int i = 0; i < E; ++i) {
        int v = in.read_int();
        int w = in.read_int();
        double weight = in.read_double();
        Edge e = new Edge(v, w, weight);
        add_edge(e);
    }
}

Edge_weighted_graph::Edge_weighted_graph(Edge_weighted_graph& G)
{
    this(G.num_vertices());
    this.E = G.num_edges();
    for (int v = 0; v < G.num_vertices(); ++v) {
        // reverse so that adjacency list is in same order as original
        Stack <Edge> reverse = new Stack<Edge>();
        for (Edge e : G.adj[v]) {
            reverse.push(e);
        }
        for (Edge e : reverse) {
            adj[v].add(e);
        }
    }
}

int Edge_weighted_graph::num_vertices()
{
    return V;
}

int Edge_weighted_graph::num_edges()
{
    return E;
}

void Edge_weighted_graph::add_edge(Edge& e)
{
    int v = e.either();
    int w = e.other(v);
    validateVertex(v);
    validateVertex(w);
    adj[v].add(e);
    adj[w].add(e);
    ++E;
}

std::vector<Edge> Edge_weighted_graph::adj(int v)
{
    validateVertex(v);
    return adj[v];
}

int Edge_weighted_graph::degree(int v)
{
    validateVertex(v);
    return adj[v].size();
}

std::vector<Edge> Edge_weighted_graph::edges()
{
    Bag <Edge> list = new Bag<Edge>();
    for (int v = 0; v < V; ++v) {
        int selfLoops = 0;
        for (Edge e : adjacent(v)) {
            if (e.other(v) > v) {
                list.add(e);
            }
                // only add one copy of each self loop (self loops will be consecutive)
            else if (e.other(v) == v) {
                if (selfLoops % 2 == 0) { list.add(e); }
                ++selfLoops;
            }
        }
    }
    return list;
}

std::string Edge_weighted_graph::to_string()
{
    std::stringstream s = new std::stringstream();
    s.append(V + " " + E + NEWLINE);
    for (int v = 0; v < V; ++v) {
        s.append(v + ": ");
        for (Edge e : adj[v]) {
            s.append(e + "  ");
        }
        s.append(NEWLINE);
    }
    return s.to_string();
}

void Edge_weighted_graph::validateVertex(int v)
{
    if (v < 0 || v >= V) {
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
    }
}

std::ostream& operator<<(std::ostream& os, Edge_weighted_graph& out)
{
    return os << out.to_string();
}
