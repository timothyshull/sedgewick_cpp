#include "Directed_eulerian_path.h"
#include "Std_out.h"
#include "Breadth_first_paths.h"

Directed_eulerian_path::Directed_eulerian_path(Digraph& digraph)
{
    int deficit{0};
    int s{_non_isolated_vertex(digraph)};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) > digraph.indegree(v)) {
            deficit += (digraph.outdegree(v) - digraph.indegree(v));
            s = v;
        }
    }

    if (deficit > 1) { return; }

    if (s == -1) { s = 0; }

    std::vector<std::vector<int>::iterator> adj;
    adj.reserve(static_cast<std::vector<std::vector<int>::iterator>::size_type>(digraph.num_vertices()));
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        adj[v] = digraph.adjacent(v).begin();
    }

    Stack<int> stack;
    stack.push(s);
    _path = Stack<int>{};
    int v;
    while (!stack.is_empty()) {
        v = stack.pop();
        for (auto it = adj[v]; it != digraph.adjacent(v).end(); ++it) {
            stack.push(v); // TODO: fix all of this
            v = *(adj[v]++);
        }
        // push vertex with no more available edges to path
        _path.push(v);
    }

    if (_path.size() != digraph.num_edges() + 1) {
        _path = Stack<int>{};
    }

    utility::alg_assert(_check(digraph), "Directed_eulerian_path invariant check failed after construction");
}

int Directed_eulerian_path::_non_isolated_vertex(Digraph& digraph)
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Directed_eulerian_path::_has_eulerian_path(Digraph& digraph)
{
    if (digraph.num_edges() == 0) { return true; }

    int deficit{0};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) > digraph.indegree(v)) {
            deficit += (digraph.outdegree(v) - digraph.indegree(v));
        }
    }
    if (deficit > 1) { return false; }

    Graph graph{digraph.num_vertices()};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        for (auto w : digraph.adjacent(v)) {
            graph.add_edge(v, w);
        }
    }

    int s{_non_isolated_vertex(digraph)};
    Breadth_first_paths bfs{graph, s};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (graph.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Directed_eulerian_path::_check(Digraph& digraph)
{
    if (has_eulerian_path() == (path().is_empty())) { return false; }

    if (has_eulerian_path() != _has_eulerian_path(digraph)) { return false; }

    if (_path.is_empty()) { return true; }

    return _path.size() == digraph.num_edges() + 1;
}

void Directed_eulerian_path::unit_test(Digraph& digraph, std::string&& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(digraph);

    Directed_eulerian_path euler{digraph};

    Std_out::print("Eulerian path:  ");
    if (euler.has_eulerian_path()) {
        for (int v : euler.path()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("none");
    }
    Std_out::print_line();
}
