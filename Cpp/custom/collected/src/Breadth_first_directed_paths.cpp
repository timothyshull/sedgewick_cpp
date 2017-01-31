#include "Breadth_first_directed_paths.h"
#include "Queue.h"

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& digraph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _distance_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices()))
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        _distance_to[v] = _infinity;
    }
    _bfs(digraph, source);
}

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& digraph, std::vector<int>& sources)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _distance_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices())),
          _edge_to(static_cast<std::vector<int>::size_type>(digraph.num_vertices()))
{
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        _distance_to[v] = _infinity;
    }
    _bfs(digraph, sources);
}

Stack<int> Breadth_first_directed_paths::path_to(int v)
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

void Breadth_first_directed_paths::_bfs(Digraph& digraph, int source)
{
    Queue<int> q;
    _marked[source] = true;
    _distance_to[source] = 0;
    q.enqueue(source);
    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : digraph.adjacent(v)) {
            if (!_marked[w]) {
                _edge_to[w] = v;
                _distance_to[w] = _distance_to[v] + 1;
                _marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}

void Breadth_first_directed_paths::_bfs(Digraph& digraph, std::vector<int>& sources)
{
    Queue<int> q;
    for (int s : sources) {
        _marked[s] = true;
        _distance_to[s] = 0;
        q.enqueue(s);
    }
    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : digraph.adjacent(v)) {
            if (!_marked[w]) {
                _edge_to[w] = v;
                _distance_to[w] = _distance_to[v] + 1;
                _marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}
