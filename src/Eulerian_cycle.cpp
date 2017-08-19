#include "Eulerian_cycle.h"
#include "Queue.h"
#include "Breadth_first_paths.h"
#include "Std_out.h"

Eulerian_cycle::Edge::Edge(int v, int w) : _v{v}, _w{w}, _is_used{false} {}

int Eulerian_cycle::Edge::other(int vertex)
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
}

Eulerian_cycle::Eulerian_cycle(Graph& graph)
{
    if (graph.num_edges() == 0) { return; }

    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) % 2 != 0) {
            return;
        }
    }

    std::vector<Queue<Edge>> adj;
    adj.reserve(static_cast<std::vector<Queue<int>>::size_type>(graph.num_vertices()));
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        adj[v] = Queue<Edge>{};
    }

    int self_loops;
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        self_loops = 0;
        for (auto w : graph.adjacent(v)) {
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

    auto s = _non_isolated_vertex(graph);
    Stack<int> stack;
    stack.push(s);

    _cycle = Stack<int>{};
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
        _cycle.push(v);
    }

    if (_cycle.size() != graph.num_edges() + 1) {
        _cycle = Stack<int>{};
    }

    utility::alg_assert(_certify_solution(graph), "Eulerian_cycle solution verification failed");
}

int Eulerian_cycle::_non_isolated_vertex(Graph& graph)
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Eulerian_cycle::_has_eulerian_cycle(Graph& graph)
{
    if (graph.num_edges() == 0) { return false; }

    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) % 2 != 0) {
            return false;
        }
    }

    auto s = _non_isolated_vertex(graph);
    Breadth_first_paths bfs{graph, s};
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Eulerian_cycle::_certify_solution(Graph& graph)
{
    if (has_eulerian_cycle() == (_cycle.is_empty())) { return false; }

    if (has_eulerian_cycle() != _has_eulerian_cycle(graph)) { return false; }

    if (_cycle.is_empty()) { return true; }

    if (_cycle.size() != graph.num_edges() + 1) { return false; }

    int first = -1, last = -1;
    for (int v : _cycle) {
        if (first == -1) { first = v; }
        last = v;
    }
    return first == last;
}

void Eulerian_cycle::unit_test(Graph& graph, std::string&& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(graph);

    Eulerian_cycle euler{graph};

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
