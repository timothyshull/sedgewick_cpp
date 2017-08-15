#include "Bipartite_x.h"
#include "Stack.h"

Bipartite_x::Bipartite_x(Graph& graph)
        : _is_bipartite{true},
          _color(graph.num_vertices()),
          _marked(graph.num_vertices()),
          _edge_to(graph.num_vertices())
{
    for (int v = 0; v < graph.num_vertices() && _is_bipartite; ++v) {
        if (!_marked[v]) {
            _bfs(graph, v);
        }
    }
    utility::alg_assert(_check(graph), "Bipartite_x invariant check failed after constructor");
}

Bipartite_x_color Bipartite_x::color(int vertex) const
{
    if (!_is_bipartite) {
        throw utility::Unsupported_operation_exception{"Graph is not bipartite"};
    }
    return _color[vertex];
}

void Bipartite_x::_bfs(Graph& graph, int source)
{
    Queue<int> q;
    _color[source] = Bipartite_x_color::white;
    _marked[source] = true;
    q.enqueue(source);

    while (!q.is_empty()) {
        auto v = q.dequeue();
        for (auto w : graph.adjacent(v)) {
            if (!_marked[w]) {
                _marked[w] = true;
                _edge_to[w] = v;
                _color[w] = !_color[v];
                q.enqueue(w);
            } else if (_color[w] == _color[v]) {
                _is_bipartite = false;

                _cycle = Queue<int>{};
                Stack<int> stack;
                auto x = v;
                auto y = w;
                while (x != y) {
                    stack.push(x);
                    _cycle.enqueue(y);
                    x = _edge_to[x];
                    y = _edge_to[y];
                }
                stack.push(x);
                while (!stack.is_empty()) {
                    _cycle.enqueue(stack.pop());
                }
                _cycle.enqueue(w);
                return;
            }
        }
    }
}

bool Bipartite_x::_check(Graph& graph) const
{
    if (_is_bipartite) {
        for (int v = 0; v < graph.num_vertices(); ++v) {
            for (auto w : graph.adjacent(v)) {
                if (_color[v] == _color[w]) {
                    std::cerr << "There is an edge " << v << "-" << w << " with " << v << " and " << w << " in the same side of bipartition\n";
                    return false;
                }
            }
        }
    } else {
        auto first = -1;
        auto last = -1;
        for (auto v : odd_cycle()) {
            if (first == -1) { first = v; }
            last = v;
        }
        if (first != last) {
            std::cerr << "The cycle begins with " << first << " and ends with " << last << "\n";
            return false;
        }
    }
    return true;
}
