#include "Kosaraju_sharir_scc.h"
#include "Depth_first_order.h"
#include "Transitive_closure.h"

Kosaraju_sharir_scc::Kosaraju_sharir_scc(Digraph& digraph)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices())),
          _id(static_cast<std::vector<int>::size_type>(digraph.num_vertices()))
{
    Digraph reversed{digraph.reverse()};
    Depth_first_order dfs{reversed};

    for (int v : dfs.reverse_post()) {
        if (!_marked[v]) {
            _dfs(digraph, v);
            ++_count;
        }
    }

    utility::alg_assert(_check(digraph), "Kosaraju_sharir_scc invariant check failed after construction");
}

void Kosaraju_sharir_scc::_dfs(Digraph& digraph, int vertex)
{
    _marked[vertex] = true;
    _id[vertex] = _count;
    for (int w : digraph.adjacent(vertex)) {
        if (!_marked[w]) { _dfs(digraph, w); }
    }
}

bool Kosaraju_sharir_scc::_check(Digraph& digraph)
{
    Transitive_closure tc{digraph};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        for (int w{0}; w < digraph.num_vertices(); ++w) {
            if (strongly_connected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v))) {
                return false;
            }
        }
    }
    return true;
}
