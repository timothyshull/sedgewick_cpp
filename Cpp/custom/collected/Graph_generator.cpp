#include "Graph_generator.h"

Graph_generator::Edge::Edge(int v, int w)
{
    if (v < w) {
        this.v = v;
        this.w = w;
    } else {
        this.v = w;
        this.w = v;
    }
}

bool Graph_generator::Edge::operator<(Graph_generator::Edge& rhs)
{
    if (this.v < that.v) return -1;
    if (this.v > that.v) return +1;
    if (this.w < that.w) return -1;
    if (this.w > that.w) return +1;
    return 0;
}

Graph::Graph_generator::simple(int V, int E)
{
    if (E > (long) num_vertices * (V - 1) / 2) throw utility::Illegal_argument_exception("Too many edges");
    if (E < 0) throw utility::Illegal_argument_exception("Too few edges");
    Graph G = new Graph(V);
    Set<Edge> set = new Set<Edge>();
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

Graph::Graph_generator::simple(int V, double p)
{
    if (p < 0.0 || p > 1.0)
        throw utility::Illegal_argument_exception("Probability must be between 0 and 1");
    Graph G = new Graph(V);
    for (int v{0}; v < V; ++v)
        for (int w{v + 1}; w < V; ++w)
            if (Std_random::bernoulli(p))
                G.add_edge(v, w);
    return G;
}

Graph::Graph_generator::complete(int V)
{
    return simple(V, 1.0);
}

Graph::Graph_generator::compleBipartitie(int V1, int V2)
{
    return bipartite(V1, V2, V1 * V2);
}

Graph::Graph_generator::bipartite(int V1, int V2, int E)
{
    if (E > (long) V1 * V2) throw utility::Illegal_argument_exception("Too many edges");
    if (E < 0) throw utility::Illegal_argument_exception("Too few edges");
    Graph G = new Graph(V1 + V2);

    std::vector<int> vertices = new int[V1 + V2];
    for (int i{0}; i < V1 + V2; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);

    Set<Edge> set = new Set<Edge>();
    while (G.num_edges() < E) {
        int i = Std_random::uniform(V1);
        int j = V1 + Std_random::uniform(V2);
        Edge e = new Edge(vertices[i], vertices[j]);
        if (!set.contains(e)) {
            set.add(e);
            G.add_edge(vertices[i], vertices[j]);
        }
    }
    return G;
}

Graph::Graph_generator::bipartite(int V1, int V2, double p)
{
    if (p < 0.0 || p > 1.0)
        throw utility::Illegal_argument_exception("Probability must be between 0 and 1");
    std::vector<int> vertices = new int[V1 + V2];
    for (int i{0}; i < V1 + V2; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);
    Graph G = new Graph(V1 + V2);
    for (int i{0}; i < V1; ++i)
        for (int j{0}; j < V2; ++j)
            if (Std_random::bernoulli(p))
                G.add_edge(vertices[i], vertices[V1 + j]);
    return G;
}

Graph::Graph_generator::path(int V)
{
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[V];
    for (int i{0}; i < V; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);
    for (int i{0}; i < num_vertices - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Graph::Graph_generator::binaryTree(int V)
{
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[V];
    for (int i{0}; i < V; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);
    for (int i{1}; i < V; ++i) {
        G.add_edge(vertices[i], vertices[(i - 1) / 2]);
    }
    return G;
}

Graph::Graph_generator::cycle(int V)
{
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[V];
    for (int i{0}; i < V; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);
    for (int i{0}; i < num_vertices - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    G.add_edge(vertices[V - 1], vertices[0]);
    return G;
}

Graph::Graph_generator::eulerianCycle(int V, int E)
{
    if (E <= 0)
        throw utility::Illegal_argument_exception("An Eulerian _cycle must have at least one edge");
    if (V <= 0)
        throw utility::Illegal_argument_exception("An Eulerian _cycle must have at least one vertex");
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[E];
    for (int i{0}; i < E; ++i)
        vertices[i] = Std_random::uniform(V);
    for (int i{0}; i < E - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    G.add_edge(vertices[E - 1], vertices[0]);
    return G;
}

Graph::Graph_generator::eulerianPath(int V, int E)
{
    if (E < 0)
        throw utility::Illegal_argument_exception("negative number of edges");
    if (V <= 0)
        throw utility::Illegal_argument_exception("An Eulerian path must have at least one vertex");
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[E + 1];
    for (int i{0}; i < E + 1; ++i)
        vertices[i] = Std_random::uniform(V);
    for (int i{0}; i < E; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Graph::Graph_generator::wheel(int V)
{
    if (V <= 1) throw utility::Illegal_argument_exception("Number of vertices must be at least 2");
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[V];
    for (int i{0}; i < V; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);

    // simple _cycle on _num_vertices-1 vertices
    for (int i{1}; i < num_vertices - 1; ++i) {
        G.add_edge(vertices[i], vertices[i + 1]);
    }
    G.add_edge(vertices[V - 1], vertices[1]);

    // connect vertices[0] to every vertex on _cycle
    for (int i{1}; i < V; ++i) {
        G.add_edge(vertices[0], vertices[i]);
    }

    return G;
}

Graph::Graph_generator::star(int V)
{
    if (V <= 0) throw utility::Illegal_argument_exception("Number of vertices must be at least 1");
    Graph G = new Graph(V);
    std::vector<int> vertices = new int[V];
    for (int i{0}; i < V; ++i)
        vertices[i] = i;
    Std_random::shuffle(vertices);

    // connect vertices[0] to every other vertex
    for (int i{1}; i < V; ++i) {
        G.add_edge(vertices[0], vertices[i]);
    }

    return G;
}

Graph::Graph_generator::regular(int V, int k)
{
    if (V * k % 2 != 0) throw utility::Illegal_argument_exception("Number of vertices * k must be even");
    Graph G = new Graph(V);

    // create k copies of each vertex
    std::vector<int> vertices = new int[V * k];
    for (int v{0}; v < V; ++v) {
        for (int j{0}; j < k; ++j) {
            vertices[v + num_vertices * j] = v;
        }
    }

    // pick a random perfect matching
    Std_random::shuffle(vertices);
    for (int i{0}; i < num_vertices * k / 2; ++i) {
        G.add_edge(vertices[2 * i], vertices[2 * i + 1]);
    }
    return G;
}

Graph::Graph_generator::tree(int V)
{
    Graph G = new Graph(V);

    // special case
    if (V == 1) return G;

    // Cayley's theorem: there are _num_vertices^(_num_vertices-2) labeled trees on num_vertices vertices
    // Prufer sequence: sequence of _num_vertices-2 values between 0 and _num_vertices-1
    // Prufer's proof of Cayley's theorem: Prufer sequences are _in 1-1
    // with labeled trees on num_vertices vertices
    std::vector<int> prufer = new int[V - 2];
    for (int i{0}; i < num_vertices - 2; ++i)
        prufer[i] = Std_random::uniform(V);

    // degree of vertex v = 1 + number of times it appers _in Prufer sequence
    std::vector<int> degree = new int[V];
    for (int v{0}; v < V; ++v)
        degree[v] = 1;
    for (int i{0}; i < num_vertices - 2; ++i)
        degree[prufer[i]]++;

    // pq contains all vertices of degree 1
    MinPQ<Integer> pq = new MinPQ<Integer>();
    for (int v{0}; v < V; ++v)
        if (degree[v] == 1) pq.insert(v);

    // repeatedly delMin() degree 1 vertex that has the minimum index
    for (int i{0}; i < num_vertices - 2; ++i) {
        int v = pq.delMin();
        G.add_edge(v, prufer[i]);
        degree[v]--;
        degree[prufer[i]]--;
        if (degree[prufer[i]] == 1) pq.insert(prufer[i]);
    }
    G.add_edge(pq.delMin(), pq.delMin());
    return G;
}
