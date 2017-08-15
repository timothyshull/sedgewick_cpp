#include "Digraph_generator.h"
#include "utility.h"
#include "Set.h"
#include "Std_random.h"

Digraph_generator::Edge::Edge(int v, int w) : _v{v}, _w{w} {}

bool Digraph_generator::Edge::operator<(const Digraph_generator::Edge& rhs) const
{
    if (_v < rhs._v) { return true; }
    if (_v > rhs._v) { return false; }
    if (_w < rhs._w) { return true; }
    if (_w > rhs._w) { return false; }
    return false;
}

Digraph Digraph_generator::simple(int num_vertices, int num_edges)
{
    if (num_edges > static_cast<long>(num_vertices) * (num_vertices - 1)) { throw utility::Illegal_argument_exception{"Too many edges"}; }
    if (num_edges < 0) { throw utility::Illegal_argument_exception{"Too few edges"}; }
    Digraph digraph{num_vertices};
    Set<Edge> set;
    int v;
    int w;
    while (digraph.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{v, w};
        if ((v != w) && !set.contains(e)) {
            set.add(e);
            digraph.add_edge(v, w);
        }
    }
    return digraph;
}

Digraph Digraph_generator::simple(int num_vertices, double probability)
{
    if (probability < 0.0 || probability > 1.0) {
        throw utility::Illegal_argument_exception{"Probability must be between 0 and 1"};
    }
    Digraph digraph{num_vertices};
    for (auto v = 0; v < num_vertices; ++v) {
        for (auto w = 0; w < num_vertices; ++w) {
            if (v != w) {
                if (Std_random::bernoulli(probability)) {
                    digraph.add_edge(v, w);
                }
            }
        }
    }
    return digraph;
}

Digraph Digraph_generator::complete(int num_vertices)
{
    return simple(num_vertices, num_vertices * (num_vertices - 1));
}

Digraph Digraph_generator::dag(int num_vertices, int num_edges)
{
    _check_vertices_and_edges(num_vertices, num_edges);
    Digraph digraph{num_vertices};
    Set<Edge> set;

    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    int v;
    int w;
    while (digraph.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{v, w};
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            digraph.add_edge(vertices[v], vertices[w]);
        }
    }
    return digraph;
}

Digraph Digraph_generator::tournament(int num_vertices)
{
    Digraph digraph{num_vertices};
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        for (auto w = v + 1; w < digraph.num_vertices(); ++w) {
            if (Std_random::bernoulli(0.5)) { digraph.add_edge(v, w); }
            else { digraph.add_edge(w, v); }
        }
    }
    return digraph;
}

Digraph Digraph_generator::rooted_in_dag(int num_vertices, int num_edges)
{
    _check_vertices_and_edges(num_vertices, num_edges);
    Digraph digraph{num_vertices};
    Set<Edge> set;

    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    int v;
    int w;
    for (v = 0; v < num_vertices - 1; ++v) {
        w = Std_random::uniform(v + 1, num_vertices);
        Edge e{v, w};
        set.add(e);
        digraph.add_edge(vertices[v], vertices[w]);
    }

    while (digraph.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{v, w};
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            digraph.add_edge(vertices[v], vertices[w]);
        }
    }
    return digraph;
}

Digraph Digraph_generator::rooted_out_dag(int num_vertices, int num_edges)
{
    _check_vertices_and_edges(num_vertices, num_edges);
    Digraph digraph{num_vertices};
    Set<Edge> set;

    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    int v;
    int w;
    for (v = 0; v < num_vertices - 1; ++v) {
        w = Std_random::uniform(v + 1, num_vertices);
        Edge e{w, v};
        set.add(e);
        digraph.add_edge(vertices[w], vertices[v]);
    }

    while (digraph.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{w, v};
        if ((v < w) && !set.contains(e)) {
            set.add(e);
            digraph.add_edge(vertices[w], vertices[v]);
        }
    }
    return digraph;
}

Digraph Digraph_generator::rooted_in_tree(int num_vertices)
{
    return rooted_in_dag(num_vertices, num_vertices - 1);
}

Digraph Digraph_generator::rooted_out_tree(int num_vertices)
{
    return rooted_out_dag(num_vertices, num_vertices - 1);
}

Digraph Digraph_generator::path(int num_vertices)
{
    Digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    for (auto i = 0; i < num_vertices - 1; ++i) {
        digraph.add_edge(vertices[i], vertices[i + 1]);
    }

    return digraph;
}

Digraph Digraph_generator::binary_tree(int num_vertices)
{
    Digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    for (auto i = 1; i < num_vertices; ++i) {
        digraph.add_edge(vertices[i], vertices[(i - 1) / 2]);
    }

    return digraph;
}

Digraph Digraph_generator::cycle(int num_vertices)
{
    Digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }

    Std_random::shuffle(vertices);

    for (auto i = 0; i < num_vertices - 1; ++i) {
        digraph.add_edge(vertices[i], vertices[i + 1]);
    }

    digraph.add_edge(vertices[num_vertices - 1], vertices[0]);

    return digraph;
}

Digraph Digraph_generator::eulerian_cycle(int num_vertices, int num_edges)
{
    if (num_edges <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian cycle must have at least one edge"};
    }
    if (num_vertices <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian cycle must have at least one vertex"};
    }

    Digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_edges; ++i) {
        vertices[i] = Std_random::uniform(num_vertices);
    }
    for (auto i = 0; i < num_edges - 1; ++i) {
        digraph.add_edge(vertices[i], vertices[i + 1]);
    }
    digraph.add_edge(vertices[num_edges - 1], vertices[0]);

    return digraph;
}

Digraph Digraph_generator::eulerian_path(int num_vertices, int num_edges)
{
    if (num_edges < 0) {
        throw utility::Illegal_argument_exception{"A digraph cannot have a negative number of edges"};
    }
    if (num_vertices <= 0) {
        throw utility::Illegal_argument_exception{"An Eulerian path must have at least one vertex"};
    }

    Digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    for (auto i = 0; i < num_edges + 1; ++i) {
        vertices[i] = Std_random::uniform(num_vertices);
    }
    for (auto i = 0; i < num_edges; ++i) {
        digraph.add_edge(vertices[i], vertices[i + 1]);
    }
    return digraph;
}

Digraph Digraph_generator::strong(int num_vertices, int num_edges, int c)
{
    if (c >= num_vertices || c <= 0) {
        throw utility::Illegal_argument_exception{"Number of components must be between 1 and _num_vertices"};
    }
    if (num_edges <= 2 * (num_vertices - c)) {
        throw utility::Illegal_argument_exception{"Number of edges must be at least 2(_num_vertices-c)"};
    }
    if (num_edges > (long) num_vertices * (num_vertices - 1) / 2) {
        throw utility::Illegal_argument_exception{"Too many edges"};
    }

    Digraph digraph{num_vertices};

    Set<Edge> set;

    std::vector<int> label;
    label.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

    int v;
    int w;
    for (v = 0; v < num_vertices; ++v) {
        label[v] = Std_random::uniform(c);
    }

    int count;
    for (auto i = 0; i < c; ++i) {
        count = 0;
        for (v = 0; v < digraph.num_vertices(); ++v) {
            if (label[v] == i) { ++count; }
        }

        std::vector<int> vertices;
        vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));

        auto j = 0;
        for (v = 0; v < num_vertices; ++v) {
            if (label[v] == i) { vertices[j++] = v; }
        }
        Std_random::shuffle(vertices);

        for (v = 0; v < count - 1; ++v) {
            w = Std_random::uniform(v + 1, count);
            Edge e{w, v};
            set.add(e);
            digraph.add_edge(vertices[w], vertices[v]);
        }

        for (v = 0; v < count - 1; ++v) {
            w = Std_random::uniform(v + 1, count);
            Edge e{v, w};
            set.add(e);
            digraph.add_edge(vertices[v], vertices[w]);
        }
    }

    while (digraph.num_edges() < num_edges) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        Edge e{v, w};
        if (!set.contains(e) && v != w && label[v] <= label[w]) {
            set.add(e);
            digraph.add_edge(v, w);
        }
    }

    return digraph;
}

void Digraph_generator::_check_vertices_and_edges(int num_vertices, int num_edges)
{
    if (num_edges > static_cast<long>(num_vertices) * (num_vertices - 1) / 2) {
        throw utility::Illegal_argument_exception{"Too many edges"};
    }
    if (num_edges < num_vertices - 1) {
        throw utility::Illegal_argument_exception{"Too few edges"};
    }
}
