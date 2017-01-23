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
    if (E > (long) V * (V - 1) / 2) throw new IllegalArgumentException("Too many edges");
    if (E < 0) throw new IllegalArgumentException("Too few edges");
    Graph G = new Graph(V);
    SET<Edge> set = new SET<Edge>();
    while (G.E() < E) {
        int v = StdRandom.uniform(V);
        int w = StdRandom.uniform(V);
        Edge e = new Edge(v, w);
        if ((v != w) && !set.contains(e)) {
            set.add(e);
            G.addEdge(v, w);
        }
    }
    return G;
}

Graph::Graph_generator::simple(int V, double p)
{
    if (p < 0.0 || p > 1.0)
        throw new IllegalArgumentException("Probability must be between 0 and 1");
    Graph G = new Graph(V);
    for (int v = 0; v < V; v++)
        for (int w = v + 1; w < V; w++)
            if (StdRandom.bernoulli(p))
                G.addEdge(v, w);
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
    if (E > (long) V1 * V2) throw new IllegalArgumentException("Too many edges");
    if (E < 0) throw new IllegalArgumentException("Too few edges");
    Graph G = new Graph(V1 + V2);

    int[] vertices = new int[V1 + V2];
    for (int i = 0; i < V1 + V2; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);

    SET<Edge> set = new SET<Edge>();
    while (G.E() < E) {
        int i = StdRandom.uniform(V1);
        int j = V1 + StdRandom.uniform(V2);
        Edge e = new Edge(vertices[i], vertices[j]);
        if (!set.contains(e)) {
            set.add(e);
            G.addEdge(vertices[i], vertices[j]);
        }
    }
    return G;
}

Graph::Graph_generator::bipartite(int V1, int V2, double p)
{
    if (p < 0.0 || p > 1.0)
        throw new IllegalArgumentException("Probability must be between 0 and 1");
    int[] vertices = new int[V1 + V2];
    for (int i = 0; i < V1 + V2; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);
    Graph G = new Graph(V1 + V2);
    for (int i = 0; i < V1; i++)
        for (int j = 0; j < V2; j++)
            if (StdRandom.bernoulli(p))
                G.addEdge(vertices[i], vertices[V1 + j]);
    return G;
}

Graph::Graph_generator::path(int V)
{
    Graph G = new Graph(V);
    int[] vertices = new int[V];
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);
    for (int i = 0; i < V - 1; i++) {
        G.addEdge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Graph::Graph_generator::binaryTree(int V)
{
    Graph G = new Graph(V);
    int[] vertices = new int[V];
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);
    for (int i = 1; i < V; i++) {
        G.addEdge(vertices[i], vertices[(i - 1) / 2]);
    }
    return G;
}

Graph::Graph_generator::cycle(int V)
{
    Graph G = new Graph(V);
    int[] vertices = new int[V];
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);
    for (int i = 0; i < V - 1; i++) {
        G.addEdge(vertices[i], vertices[i + 1]);
    }
    G.addEdge(vertices[V - 1], vertices[0]);
    return G;
}

Graph::Graph_generator::eulerianCycle(int V, int E)
{
    if (E <= 0)
        throw new IllegalArgumentException("An Eulerian cycle must have at least one edge");
    if (V <= 0)
        throw new IllegalArgumentException("An Eulerian cycle must have at least one vertex");
    Graph G = new Graph(V);
    int[] vertices = new int[E];
    for (int i = 0; i < E; i++)
        vertices[i] = StdRandom.uniform(V);
    for (int i = 0; i < E - 1; i++) {
        G.addEdge(vertices[i], vertices[i + 1]);
    }
    G.addEdge(vertices[E - 1], vertices[0]);
    return G;
}

Graph::Graph_generator::eulerianPath(int V, int E)
{
    if (E < 0)
        throw new IllegalArgumentException("negative number of edges");
    if (V <= 0)
        throw new IllegalArgumentException("An Eulerian path must have at least one vertex");
    Graph G = new Graph(V);
    int[] vertices = new int[E + 1];
    for (int i = 0; i < E + 1; i++)
        vertices[i] = StdRandom.uniform(V);
    for (int i = 0; i < E; i++) {
        G.addEdge(vertices[i], vertices[i + 1]);
    }
    return G;
}

Graph::Graph_generator::wheel(int V)
{
    if (V <= 1) throw new IllegalArgumentException("Number of vertices must be at least 2");
    Graph G = new Graph(V);
    int[] vertices = new int[V];
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);

    // simple cycle on V-1 vertices
    for (int i = 1; i < V - 1; i++) {
        G.addEdge(vertices[i], vertices[i + 1]);
    }
    G.addEdge(vertices[V - 1], vertices[1]);

    // connect vertices[0] to every vertex on cycle
    for (int i = 1; i < V; i++) {
        G.addEdge(vertices[0], vertices[i]);
    }

    return G;
}

Graph::Graph_generator::star(int V)
{
    if (V <= 0) throw new IllegalArgumentException("Number of vertices must be at least 1");
    Graph G = new Graph(V);
    int[] vertices = new int[V];
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    StdRandom.shuffle(vertices);

    // connect vertices[0] to every other vertex
    for (int i = 1; i < V; i++) {
        G.addEdge(vertices[0], vertices[i]);
    }

    return G;
}

Graph::Graph_generator::regular(int V, int k)
{
    if (V * k % 2 != 0) throw new IllegalArgumentException("Number of vertices * k must be even");
    Graph G = new Graph(V);

    // create k copies of each vertex
    int[] vertices = new int[V * k];
    for (int v = 0; v < V; v++) {
        for (int j = 0; j < k; j++) {
            vertices[v + V * j] = v;
        }
    }

    // pick a random perfect matching
    StdRandom.shuffle(vertices);
    for (int i = 0; i < V * k / 2; i++) {
        G.addEdge(vertices[2 * i], vertices[2 * i + 1]);
    }
    return G;
}

Graph::Graph_generator::tree(int V)
{
    Graph G = new Graph(V);

    // special case
    if (V == 1) return G;

    // Cayley's theorem: there are V^(V-2) labeled trees on V vertices
    // Prufer sequence: sequence of V-2 values between 0 and V-1
    // Prufer's proof of Cayley's theorem: Prufer sequences are in 1-1
    // with labeled trees on V vertices
    int[] prufer = new int[V - 2];
    for (int i = 0; i < V - 2; i++)
        prufer[i] = StdRandom.uniform(V);

    // degree of vertex v = 1 + number of times it appers in Prufer sequence
    int[] degree = new int[V];
    for (int v = 0; v < V; v++)
        degree[v] = 1;
    for (int i = 0; i < V - 2; i++)
        degree[prufer[i]]++;

    // pq contains all vertices of degree 1
    MinPQ<Integer> pq = new MinPQ<Integer>();
    for (int v = 0; v < V; v++)
        if (degree[v] == 1) pq.insert(v);

    // repeatedly delMin() degree 1 vertex that has the minimum index
    for (int i = 0; i < V - 2; i++) {
        int v = pq.delMin();
        G.addEdge(v, prufer[i]);
        degree[v]--;
        degree[prufer[i]]--;
        if (degree[prufer[i]] == 1) pq.insert(prufer[i]);
    }
    G.addEdge(pq.delMin(), pq.delMin());
    return G;
}
