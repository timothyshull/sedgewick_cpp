#include "Eulerian_path.h"
#include "Queue.h"
#include "Breadth_first_paths.h"
#include "Std_out.h"

Eulerian_path::Edge::Edge(int v, int w) : _v{v}, _w{w}, _is_used{false} {}

int Eulerian_path::Edge::other(int vertex)
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw utility::Illegal_argument_exception("Illegal endpoint"); }
}

Eulerian_path::Eulerian_path(Graph& graph)
{
    int odd_degree_vertices{0};
    int s{_non_isolated_vertex(graph)};
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) % 2 != 0) {
            ++odd_degree_vertices;
            s = v;
        }
    }

    if (odd_degree_vertices > 2) { return; }

    if (s == -1) { s = 0; }

    std::vector<Queue<Edge>> adj;
    adj.reserve(static_cast<std::vector<Queue<Edge>>::size_type>(graph.num_vertices()));
    for (int v{0}; v < graph.num_vertices(); ++v) {
        adj[v] = Queue<Edge>{};
    }

    int self_loops;
    for (int v{0}; v < graph.num_vertices(); ++v) {
        self_loops = 0;
        for (int w : graph.adjacent(v)) {
            if (v == w) {
                if (self_loops % 2 == 0) {
                    Edge e{v, w};
                    adj[v].enqueue(e);
                    adj[w].enqueue(e);
                }
                ++self_loops;
            } else if (v < w) {
                Edge e{v, w};
                adj[v].enqueue(e);
                adj[w].enqueue(e);
            }
        }
    }

    Stack<int> stack;
    stack.push(s);

    _path = Stack<int>();
    int v;
    while (!stack.is_empty()) {
        v = stack.pop();
        while (!adj[v].is_empty()) {
            Edge edge = adj[v].dequeue();
            if (edge._is_used) { continue; }
            edge._is_used = true;
            stack.push(v);
            v = edge.other(v);
        }
        _path.push(v);
    }

    if (_path.size() != graph.num_edges() + 1) {
        _path = Stack<int>{};
    }

    utility::alg_assert(_certify_solution(graph), "Eulerian_path solution certification failed");
}

int Eulerian_path::_non_isolated_vertex(Graph& graph)
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Eulerian_path::_has_eulerian_path(Graph& graph)
{
    if (graph.num_edges() == 0) { return true; }

    int oddDegreeVertices = 0;
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) % 2 != 0) {
            ++oddDegreeVertices;
        }
    }
    if (oddDegreeVertices > 2) { return false; }

    int s = _non_isolated_vertex(graph);
    Breadth_first_paths bfs{graph, s};
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Eulerian_path::_certify_solution(Graph& graph)
{
    if (has_eulerian_path() == (_path.is_empty())) { return false; }

    if (has_eulerian_path() != _has_eulerian_path(graph)) { return false; }

    if (_path.is_empty()) { return true; }

    return _path.size() == graph.num_edges() + 1;
}

void Eulerian_path::unit_test(Graph& graph, std::string&& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(graph);

    Eulerian_path euler{graph};

    Std_out::print("Eulerian path:  ");
    if (euler.has_eulerian_path()) {
        for (auto v : euler.path()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("none");
    }
    Std_out::print_line();
}
