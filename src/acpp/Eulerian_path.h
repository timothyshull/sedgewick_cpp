// Program 17.18 - Euler path existence
// Program 17.19 - Linear-time Euler path
#ifndef EULERIAN_PATH_EXISTENCE_H
#define EULERIAN_PATH_EXISTENCE_H

#include <stack>
#include <iostream>

#include "Edge.h"
#include "Vertex_degrees.h"

template<typename Graph>
class Eulerian_path {
public:
    Eulerian_path(const Graph& graph, int source, int destination)
            : _graph{graph},
              _source{source},
              _destination{destination}
    {
        Vertex_degrees<Graph> deg{graph};
        int t{deg[source] + deg[destination]};
        if ((t % 2) != 0) {
            _found = false;
            return;
        }
        for (t = 0; t < graph.num_vertices(); ++t) {
            if ((t != source) && (t != destination)) {
                if ((deg[t] % 2) != 0) {
                    _found = false;
                    return;
                }
            }
        }
        _found = true;
    }

    inline bool exists() const noexcept { return _found; }

    void show()
    {
        if (!_found) { return; }
        while (_tour(_source) == _source && !_stack.empty()) {
            _source = _stack.top();
            _stack.pop();
            std::cout << "-" << _source;
        }
        std::cout << "\n";
    }

private:
    Graph _graph;
    int _source;
    int _destination;
    bool _found;
    std::stack<int> _stack;

    int _tour(int v)
    {
        int w;
        while (true) {
            auto adj = _graph.adjacent(v);
            // typename Graph::adjIterator A(_graph, v);
            auto it = adj.begin();
            if (it != adj.end()) {
                w = *it;
                _stack.push(v);
                _graph.remove(Edge{v, w});
                v = w;
            } else { break; }
        }
        return v;
    }
};

#endif // EULERIAN_PATH_EXISTENCE_H
