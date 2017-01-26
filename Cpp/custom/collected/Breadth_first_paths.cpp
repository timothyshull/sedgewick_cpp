#include "Breadth_first_paths.h"
#include "Queue.h"
#include "Std_out.h"

Breadth_first_paths::Breadth_first_paths(Graph& graph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _distance_to(static_cast<std::vector<int>::size_type>(graph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
{
    _bfs(graph, source);

    utility::alg_assert(_check(graph, source), "Breadth_first_paths invariant check failed after construction");
}

Breadth_first_paths::Breadth_first_paths(Graph& graph, std::vector<int>& sources)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices())),
          _distance_to(static_cast<std::vector<int>::size_type>(graph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
{
    for (int v{0}; v < graph.num_vertices(); ++v) {
        _distance_to[v] = _infinity;
    }
    _bfs(graph, sources);
}

Stack<int> Breadth_first_paths::path_to(int v)
{
    if (!has_path_to(v)) { return {}; }
    Stack<int> path;
    int x;
    for (x = v; _distance_to[x] != 0; x = _edge_to[x]) {
        path.push(x);
    }
    path.push(x);
    return path;
}

void Breadth_first_paths::_bfs(Graph& graph, int source)
{
    Queue<int> q;
    for (int v{0}; v < graph.num_vertices(); ++v) {
        _distance_to[v] = _infinity;
    }
    _distance_to[source] = 0;
    _marked[source] = true;
    q.enqueue(source);

    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : graph.adjacent(v)) {
            if (!_marked[w]) {
                _edge_to[w] = v;
                _distance_to[w] = _distance_to[v] + 1;
                _marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}

void Breadth_first_paths::_bfs(Graph& graph, std::vector<int>& sources)
{
    Queue<int> q;
    for (int s : sources) {
        _marked[s] = true;
        _distance_to[s] = 0;
        q.enqueue(s);
    }
    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : graph.adjacent(v)) {
            if (!_marked[w]) {
                _edge_to[w] = v;
                _distance_to[w] = _distance_to[v] + 1;
                _marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}

bool Breadth_first_paths::_check(Graph& graph, int source)
{
    if (_distance_to[source] != 0) {
        Std_out::print_line("distance of source " + std::to_string(source) + " to itself = " + std::to_string(_distance_to[source]));
        return false;
    }

    for (int v{0}; v < graph.num_vertices(); ++v) {
        for (int w : graph.adjacent(v)) {
            if (has_path_to(v) != has_path_to(w)) {
                std::stringstream ss;
                ss << "The edge " << v << "-" << w << "\nhas_path_to(" << v << ") = " << has_path_to(v)
                   << "\nhas_path_to(" << w << ") = " + has_path_to(w);
                Std_out::print_line(ss.str());
                return false;
            }
            if (has_path_to(v) && (_distance_to[w] > _distance_to[v] + 1)) {
                std::stringstream ss;
                ss << "edge " << v << "-" << w << "\n_distance_to[" << v << "] = " << _distance_to[v]
                   << "\n_distance_to[" << w << "] = " << _distance_to[w];
                Std_out::print_line(ss.str());
                return false;
            }
        }
    }

    for (int w{0}; w < graph.num_vertices(); ++w) {
        if (!has_path_to(w) || w == source) { continue; }
        int v = _edge_to[w];
        if (_distance_to[w] != _distance_to[v] + 1) {
            std::stringstream ss;
            ss << "shortest path edge " << v << "-" << w << "\n_distance_to[" << v << "] = " << _distance_to[v]
               << "\n_distance_to[" << w << "] = " << _distance_to[w];
            Std_out::print_line(ss.str());
            return false;
        }
    }

    return true;
}
