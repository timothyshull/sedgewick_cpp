#include "Graph_generator.h"
#include "utility.h"
#include "Set.h"
#include "Std_random.h"
#include "Min_pq.h"

Graph_generator::Edge::Edge(int v, int w)
{
    if (v < w) {
        _v = v;
        _w = w;
    } else {
        _v = w;
        _w = v;
    }
}

bool Graph_generator::Edge::operator<(Graph_generator::Edge& rhs)
{
    if (_v < rhs._v) { return false; }
    if (_v > rhs._v) { return true; }
    if (_w < rhs._w) { return false; }
    return _w > rhs._w;
}

Graph Graph_generator::simple(int num_vertices, int num_edges)
{
    if (num_edges > (long) num_vertices * (num_vertices - 1) / 2) { throw utility::Illegal_argument_exception{"Too many edges"}; }
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Too few edges"}; }
    Graph G{num_vertices};
    Set<Edge> set;
    int v;
    int w;
    while (G.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{v, w};
        if ((v != w) && !set.contains(e)) {
            set.add(e);
            G.add_edge(v, w);
        }
    }
    return G;
}

Graph Graph_generator::simple(int num_vertices, double probability)
{
    if (probability < 0.0 || probability > 1.0) {
        throw utility::Illegal_argument_exception{"Probability must be between 0 and 1"};
    }
    Graph graph{num_vertices};
    for (auto v = 0; v < num_vertices; ++v) {
        for (auto w = v + 1; w < num_vertices; ++w) {
            if (Std_random::bernoulli(probability)) {
                graph.add_edge(v, w);
            }
        }
    }
    return graph;
}

Graph Graph_generator::complete(int num_vertices)
{
    return simple(num_vertices, 1.0);
}

Graph Graph_generator::complete_bipartite(int v1, int v2)
{
    return bipartite(v1, v2, v1 * v2);
}

Graph Graph_generator::bipartite(int v1, int v2, int num_edges)
{
    if (num_edges > (long) v1 * v2) { throw utility::Illegal_argument_exception{"Too many edges"}; }
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Too few edges"}; }
    Graph graph{v1 + v2};

    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(v1 + v2));
    for (auto i = 0; i < v1 + v2; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);

    Set<Edge> set;
    while (graph.num_edges() < num_edges) {
        int i = Std_random::uniform(v1);
        int j = v1 + Std_random::uniform(v2);
        Edge e{vertices[i], vertices[j]};
        if (!set.contains(e)) {
            set.add(e);
            graph.add_edge(vertices[i], vertices[j]);
        }
    }
    return graph;
}

Graph Graph_generator::bipartite(int v1, int v2, double probability)
{
    if (probability < 0.0 || probability > 1.0) {
        throw utility::Illegal_argument_exception{"Probability must be between 0 and 1"};
    }
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(v1 + v2));
    for (auto i = 0; i < v1 + v2; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    Graph graph{v1 + v2};
    for (auto i = 0; i < v1; ++i) {
        for (auto j = 0; j < v2; ++j) {
            if (Std_random::bernoulli(probability)) {
                graph.add_edge(vertices[i], vertices[v1 + j]);
            }
        }
    }
    return graph;
}

Graph Graph_generator::path(int num_vertices)
{
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (auto i = 0; i < num_vertices - 1; ++i) {
        graph.add_edge(vertices[i], vertices[i + 1]);
    }
    return graph;
}

Graph Graph_generator::binary_tree(int num_vertices)
{
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (auto i = 1; i < num_vertices; ++i) {
        graph.add_edge(vertices[i], vertices[(i - 1) / 2]);
    }
    return graph;
}

Graph Graph_generator::cycle(int num_vertices)
{
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (auto i = 0; i < num_vertices - 1; ++i) {
        graph.add_edge(vertices[i], vertices[i + 1]);
    }
    graph.add_edge(vertices[num_vertices - 1], vertices[0]);
    return graph;
}

Graph Graph_generator::eulerian_cycle(int num_vertices, int num_edges)
{
    if (num_edges <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian _cycle must have at least one edge"};
    }
    if (num_vertices <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian _cycle must have at least one vertex"};
    }
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_edges; ++i) {
        vertices[i] = Std_random::uniform(num_vertices);
    }
    for (auto i = 0; i < num_edges - 1; ++i) {
        graph.add_edge(vertices[i], vertices[i + 1]);
    }
    graph.add_edge(vertices[num_edges - 1], vertices[0]);
    return graph;
}

Graph Graph_generator::eulerian_path(int num_vertices, int num_edges)
{
    if (num_edges < 0) {
        throw utility::Illegal_argument_exception{"negative number of edges"};
    }
    if (num_vertices <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian path must have at least one vertex"};
    }
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_edges + 1));
    for (auto i = 0; i < num_edges + 1; ++i) {
        vertices[i] = Std_random::uniform(num_vertices);
    }
    for (auto i = 0; i < num_edges; ++i) {
        graph.add_edge(vertices[i], vertices[i + 1]);
    }
    return graph;
}

Graph Graph_generator::wheel(int num_vertices)
{
    if (num_vertices <= 1) { throw utility::Illegal_argument_exception{"Number of vertices must be at least 2"}; }
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);

    for (auto i = 1; i < num_vertices - 1; ++i) {
        graph.add_edge(vertices[i], vertices[i + 1]);
    }
    graph.add_edge(vertices[num_vertices - 1], vertices[1]);

    for (auto i = 1; i < num_vertices; ++i) {
        graph.add_edge(vertices[0], vertices[i]);
    }

    return graph;
}

Graph Graph_generator::star(int num_vertices)
{
    if (num_vertices <= 0) { throw utility::Illegal_argument_exception{"Number of vertices must be at least 1"}; }
    Graph graph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);

    for (auto i = 1; i < num_vertices; ++i) {
        graph.add_edge(vertices[0], vertices[i]);
    }

    return graph;
}

Graph Graph_generator::regular(int num_vertices, int k)
{
    if (num_vertices * k % 2 != 0) { throw utility::Illegal_argument_exception{"Number of vertices * k must be even"}; }
    Graph graph{num_vertices};

    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices * k));
    for (auto v = 0; v < num_vertices; ++v) {
        for (auto j = 0; j < k; ++j) {
            vertices[v + num_vertices * j] = v;
        }
    }

    Std_random::shuffle(vertices);
    for (auto i = 0; i < num_vertices * k / 2; ++i) {
        graph.add_edge(vertices[2 * i], vertices[2 * i + 1]);
    }
    return graph;
}

Graph Graph_generator::tree(int num_vertices)
{
    Graph graph{num_vertices};

    if (num_vertices == 1) { return graph; }

    std::vector<int> prufer;
    prufer.reserve(static_cast<std::vector<int>::size_type>(num_vertices - 2));
    for (auto i = 0; i < num_vertices - 2; ++i) {
        prufer[i] = Std_random::uniform(num_vertices);
    }

    std::vector<int> degree;
    degree.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto v = 0; v < num_vertices; ++v) {
        degree[v] = 1;
    }
    for (auto i = 0; i < num_vertices - 2; ++i) {
        degree[prufer[i]]++;
    }

    Min_pq<int> pq;
    for (auto v = 0; v < num_vertices; ++v) {
        if (degree[v] == 1) { pq.insert(v); }
    }

    for (auto i = 0; i < num_vertices - 2; ++i) {
        int v = pq.delete_min();
        graph.add_edge(v, prufer[i]);
        degree[v]--;
        degree[prufer[i]]--;
        if (degree[prufer[i]] == 1) { pq.insert(prufer[i]); }
    }
    graph.add_edge(pq.delete_min(), pq.delete_min());
    return graph;
}
