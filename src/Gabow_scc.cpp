#include "Gabow_scc.h"
#include "Transitive_closure.h"

Gabow_scc::Gabow_scc(Digraph& G)
        : _marked(static_cast<std::deque<bool>::size_type>(G.num_vertices())),
          _stack1{},
          _stack2{},
          _id(static_cast<std::vector<int>::size_type>(G.num_vertices())),
          _preorder(static_cast<std::vector<int>::size_type>(G.num_vertices()))
{
    for (auto v = 0; v < G.num_vertices(); ++v) {
        _id[v] = -1;
    }

    for (auto v = 0; v < G.num_vertices(); ++v) {
        if (!_marked[v]) { _dfs(G, v); }
    }

    utility::alg_assert(_check(G), "Gabow_scc invariant check failed after construction");
}

void Gabow_scc::_dfs(Digraph& G, int v)
{
    _marked[v] = true;
    _preorder[v] = ++_pre;
    _stack1.push(v);
    _stack2.push(v);
    for (int w : G.adjacent(v)) {
        if (!_marked[w]) { _dfs(G, w); }
        else if (_id[w] == -1) {
            while (_preorder[_stack2.peek()] > _preorder[w]) {
                _stack2.pop();
            }
        }
    }

    if (_stack2.peek() == v) {
        _stack2.pop();
        int w;
        do {
            w = _stack1.pop();
            _id[w] = _count;
        } while (w != v);
        ++_count;
    }
}

bool Gabow_scc::_check(Digraph& digraph)
{
    Transitive_closure tc{digraph};
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        for (auto w = 0; w < digraph.num_vertices(); ++w) {
            if (strongly_connected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v))) {
                return false;
            }
        }
    }
    return true;
}
