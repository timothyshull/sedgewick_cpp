#include "Digraph_generator.h"

Edge::Edge(int v, int w) : v{v}, w{w} {}

bool Edge::operator<(Edge& rhs)
{
    if (this.v < that.v) { return -1; }
    if (this.v > that.v) { return +1; }
    if (this.w < that.w) { return -1; }
    if (this.w > that.w) { return +1; }
    return 0;
}

Digraph Digraph_generator::simple(int V, int E)
{
    if (E > (long) num_vertices * (V - 1)) { throw utility::Illegal_argument_exception("Too many edges"); }
    if (E < 0) { throw utility::Illegal_argument_exception("Too few edges"); }
    Digraph G = new Digraph(V);
    Set <Edge> set = new Set<Edge>();
    while (G.num_edges() < E) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        Edge e = new Edge(v, w);
        if ((v != w) && !set.contains(e)) {
            set.add(e);
            G.add_edge(v, w);
        }
    }
    return G;
}

Digraph Digraph_generator::simple(int V, double p)
{
    if (p < 0.0 || p > 1.0) {
        throw utility::Illegal_argument_exception("Probability must be between 0 and 1");
    }
    Digraph G = new Digraph(V);
    for (int v = 0; v < V; ++v) {
        for (int w = 0; w < V; ++w) {
            if (v != w) {
                if (Std_random::bernoulli(p)) {
                    G.add_edge(v, w);
                }
            }
        }
    }
    return G;
}

Digraph Digraph_generator::complete(int V)
{
    return simple(V, num_vertices * (V - 1));
}

Digraph Digraph_generator::dag(int V, int E)
{
    if (E > (long) num_vertices * (V - 1) / 2) { throw utility::Illegal_argument_exception("Too many edges"); }
    if (E < 0) { throw utility::Illegal_argument_exception("Too few edges"); }
    Digraph G = new Digraph(V);
    Set <Edge> set = new Set<Edge>();
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    while (G.num_edges() < E) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        Edge e = new Edge(v, w);
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            G.add_edge(vertices[v], vertices[w]);
        }
    }
    return G;
}

Digraph Digraph_generator::tournament(int V)
{
    Digraph G = new Digraph(V);
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (int w = v + 1; w < G.num_vertices(); ++w) {
            if (Std_random::bernoulli(0.5)) { G.add_edge(v, w); }
            else { G.add_edge(w, v); }
        }
    }
    return G;
}

Digraph Digraph_generator::rooted_in_dag(int V, int E)
{
    if (E > (long) num_vertices * (V - 1) / 2) { throw utility::Illegal_argument_exception("Too many edges"); }
    if (E < num_vertices - 1) { throw utility::Illegal_argument_exception("Too few edges"); }
    Digraph G = new Digraph(V);
    Set <Edge> set = new Set<Edge>();

    // fix a topological order
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);

    // one edge pointing from each vertex, other than the root = vertices[_num_vertices-1]
    for (int v = 0; v < num_vertices - 1; ++v) {
        int w = Std_random::uniform(v + 1, V);
        Edge e = new Edge(v, w);
        set.add(e);
        G.add_edge(vertices[v], vertices[w]);
    }

    while (G.num_edges() < E) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        Edge e = new Edge(v, w);
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            G.add_edge(vertices[v], vertices[w]);
        }
    }
    return G;
}

Digraph Digraph_generator::rooted_out_dag(int V, int E)
{
    if (E > (long) num_vertices * (V - 1) / 2) { throw utility::Illegal_argument_exception("Too many edges"); }
    if (E < num_vertices - 1) { throw utility::Illegal_argument_exception("Too few edges"); }
    Digraph G = new Digraph(V);
    Set <Edge> set = new Set<Edge>();

    // fix a topological order
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);

    // one edge pointing from each vertex, other than the root = vertices[_num_vertices-1]
    for (int v = 0; v < num_vertices - 1; ++v) {
        int w = Std_random::uniform(v + 1, V);
        Edge e = new Edge(w, v);
        set.add(e);
        G.add_edge(vertices[w], vertices[v]);
    }

    while (G.num_edges() < E) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        Edge e = new Edge(w, v);
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            G.add_edge(vertices[w], vertices[v]);
        }
    }
    return G;
}

Digraph Digraph_generator::rooted_in_tree(int V)
{
    return rooted_in_dag(V, num_vertices - 1);
}

Digraph Digraph_generator::rooted_out_tree(int V)
{
    return rooted_out_dag(V, num_vertices - 1);
}

Digraph Digraph_generator::path(int V)
{
    Digraph G = new Digraph(V);
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (int i = 0; i < num_vertices - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Digraph Digraph_generator::binary_tree(int V)
{
    Digraph G = new Digraph(V);
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (int i = 1; i < V; ++i) {
        G.add_edge(vertices[i], vertices[(i - 1) / 2]);
    }
    return G;
}

Digraph Digraph_generator::cycle(int V)
{
    Digraph G = new Digraph(V);
    int
    []
    vertices = new int[V];
    for (int i = 0; i < V; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (int i = 0; i < num_vertices - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    G.add_edge(vertices[V - 1], vertices[0]);
    return G;
}

Digraph Digraph_generator::eulerian_cycle(int V, int E)
{
    if (E <= 0) {
        throw utility::Illegal_argument_exception("An Eulerian cycle must have at least one edge");
    }
    if (V <= 0) {
        throw utility::Illegal_argument_exception("An Eulerian cycle must have at least one vertex");
    }
    Digraph G = new Digraph(V);
    int
    []
    vertices = new int[E];
    for (int i = 0; i < E; ++i) {
        vertices[i] = Std_random::uniform(V);
    }
    for (int i = 0; i < E - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    G.add_edge(vertices[E - 1], vertices[0]);
    return G;
}

Digraph Digraph_generator::eulerian_path(int V, int E)
{
    if (E < 0) {
        throw utility::Illegal_argument_exception("negative number of edges");
    }
    if (V <= 0) {
        throw utility::Illegal_argument_exception("An Eulerian path must have at least one vertex");
    }
    Digraph G = new Digraph(V);
    int
    []
    vertices = new int[E + 1];
    for (int i = 0; i < E + 1; ++i) {
        vertices[i] = Std_random::uniform(V);
    }
    for (int i = 0; i < E; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Digraph Digraph_generator::strong(int V, int E, int c)
{
    if (c >= num_vertices || c <= 0) {
        throw utility::Illegal_argument_exception("Number of components must be between 1 and _num_vertices");
    }
    if (E <= 2 * (V - c)) {
        throw utility::Illegal_argument_exception("Number of edges must be at least 2(_num_vertices-c)");
    }
    if (E > (long) num_vertices * (V - 1) / 2) {
        throw utility::Illegal_argument_exception("Too many edges");
    }

    // the digraph
    Digraph G = new Digraph(V);

    // edges added to G (to avoid duplicate edges)
    Set <Edge> set = new Set<Edge>();

    int
    []
    label = new int[V];
    for (int v = 0; v < V; ++v) {
        label[v] = Std_random::uniform(c);
    }

    // make all vertices with label c a strong component by
    // combining a rooted in-tree and a rooted out-tree
    for (int i = 0; i < c; ++i) {
        // how many vertices in component c
        int count = 0;
        for (int v = 0; v < G.num_vertices(); ++v) {
            if (label[v] == i) { ++count; }
        }

        // if (count == 0) System.err.print_line("less than desired number of strong components");

        int
        []
        vertices = new int[count];
        int j = 0;
        for (int v = 0; v < V; ++v) {
            if (label[v] == i) { vertices[j++] = v; }
        }
        Std_random::shuffle(vertices);

        // rooted-in tree with root = vertices[count-1]
        for (int v = 0; v < count - 1; ++v) {
            int w = Std_random::uniform(v + 1, count);
            Edge e = new Edge(w, v);
            set.add(e);
            G.add_edge(vertices[w], vertices[v]);
        }

        // rooted-out tree with root = vertices[count-1]
        for (int v = 0; v < count - 1; ++v) {
            int w = Std_random::uniform(v + 1, count);
            Edge e = new Edge(v, w);
            set.add(e);
            G.add_edge(vertices[v], vertices[w]);
        }
    }

    while (G.num_edges() < E) {
        int v = Std_random::uniform(V);
        int w = Std_random::uniform(V);
        Edge e = new Edge(v, w);
        if (!set.contains(e) && v != w && label[v] <= label[w]) {
            set.add(e);
            G.add_edge(v, w);
        }
    }

    return G;
}
