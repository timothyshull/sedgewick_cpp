#include "Directed_eulerian_cycle.h"
#include "Std_out.h"
#include "Graph.h"
#include "Breadth_first_paths.h"

Directed_eulerian_cycle::Directed_eulerian_cycle(Digraph& digraph)
{
    if (digraph.num_edges() == 0) { return; }

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) != digraph.indegree(v)) {
            return;
        }
    }

    std::vector<typename std::vector<int>::iterator> adj;
    adj.reserve(static_cast<std::vector<int>::size_type>(digraph.num_vertices()));
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        adj[v] = digraph.adjacent(v).begin();
    }

    auto s = _non_isolated_vertex(digraph);
    Stack<int> stack;
    stack.push(s);

    _cycle = Stack<int>{};
    int v;
    while (!stack.is_empty()) {
        v = stack.pop();
        for (auto it = adj[v]; it != digraph.adjacent(v).end(); ++it) {
            stack.push(v);
            v = *it; // TODO: this might leave v one iteration value behind, check v = adj[v].next();
        }
        _cycle.push(v);
    }

    if (_cycle.size() != digraph.num_edges() + 1) {
        _cycle = Stack<int>{};
    }

    utility::alg_assert(_certify_solution(digraph), "Directed_eulerian_cycle solution certification failed after construction");
}

int Directed_eulerian_cycle::_non_isolated_vertex(Digraph& digraph)
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Directed_eulerian_cycle::_has_eulerian_cycle(Digraph& digraph)
{
    if (digraph.num_edges() == 0) { return false; }

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (digraph.outdegree(v) != digraph.indegree(v)) {
            return false;
        }
    }

    Graph graph{digraph.num_vertices()};
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        for (auto w : digraph.adjacent(v)) {
            graph.add_edge(v, w);
        }
    }

    auto s = _non_isolated_vertex(digraph);
    Breadth_first_paths bfs{graph, s};
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (graph.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Directed_eulerian_cycle::_certify_solution(Digraph& digraph)
{
    if (has_eulerian_cycle() == (!cycle().is_empty())) { return false; }

    if (has_eulerian_cycle() != _has_eulerian_cycle(digraph)) { return false; }

    if (_cycle.is_empty()) { return true; }

    return _cycle.size() == digraph.num_edges() + 1;
}

void Directed_eulerian_cycle::unit_test(Digraph& digraph, std::string&& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(digraph);

    Directed_eulerian_cycle euler{digraph};

    Std_out::print("Eulerian _cycle: ");
    if (euler.has_eulerian_cycle()) {
        for (int v : euler.cycle()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("none");
    }
    Std_out::print_line();
}
