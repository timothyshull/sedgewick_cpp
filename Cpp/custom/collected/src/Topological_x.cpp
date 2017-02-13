#include <deque>
#include "Topological_x.h"

Topological_x::Topological_x(Digraph& digraph)
        : _rank(digraph.num_vertices()),
          _order{}
{
    std::vector<int> indegree;
    indegree.reserve(digraph.num_vertices());
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        indegree[v] = digraph.indegree(v);
    }

    int count{0};

    Queue<int> queue;
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (indegree[v] == 0) { queue.enqueue(v); }
    }

    for (int j{0}; !queue.is_empty(); ++j) {
        int v = queue.dequeue();
        _order.enqueue(v);
        _rank[v] = ++count;
        for (auto w : digraph.adjacent(v)) {
            indegree[w]--;
            if (indegree[w] == 0) { queue.enqueue(w); }
        }
    }

    if (count != digraph.num_vertices()) {
        _order = Queue<int>{};
    }

    utility::alg_assert(_check(digraph), "Topological_x invariant check failed after construction with a digraph");
}

Topological_x::Topological_x(Edge_weighted_digraph& digraph)
        : _rank(digraph.num_vertices()),
          _order{}
{
    std::vector<int> indegree;
    indegree.reserve(digraph.num_vertices());
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        indegree[v] = digraph.indegree(v);
    }

    int count{0};

    Queue<int> queue;
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (indegree[v] == 0) { queue.enqueue(v); }
    }

    for (int j{0}; !queue.is_empty(); ++j) {
        int v = queue.dequeue();
        _order.enqueue(v);
        _rank[v] = ++count;
        for (auto e : digraph.adjacent(v)) {
            int w = e.to();
            indegree[w]--;
            if (indegree[w] == 0) { queue.enqueue(w); }
        }
    }

    if (count != digraph.num_vertices()) {
        _order = Queue<int>{};
    }

    utility::alg_assert(_check(digraph), "Topological_x invariant check failed after construction with a edge weighted digraph");
}

int Topological_x::rank(int v)
{
    _validate_vertex(v);
    if (has_order()) { return _rank[v]; }
    else { return -1; }
}

bool Topological_x::_check(Digraph& digraph)
{
    if (has_order()) {
        std::deque<bool> found{static_cast<std::deque<bool>::size_type>(digraph.num_vertices())};
        for (int i{0}; i < digraph.num_vertices(); ++i) {
            found[rank(i)] = true;
        }
        for (int i{0}; i < digraph.num_vertices(); ++i) {
            if (!found[i]) {
                std::cerr << "No vertex with rank " + i;
                return false;
            }
        }

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            for (auto w : digraph.adjacent(v)) {
                if (rank(v) > rank(w)) {
                    std::cerr << v << "-" << w << ": rank(" << v << ") = " << rank(v) << ", rank(" << w << ") = " << rank(w) << "\n";
                    return false;
                }
            }
        }

        int r{0};
        for (auto v : order()) {
            if (rank(v) != r) {
                std::cerr << "_order() and rank() inconsistent";
                return false;
            }
            ++r;
        }
    }

    return true;
}

bool Topological_x::_check(Edge_weighted_digraph& digraph)
{
    if (has_order()) {
        std::deque<bool> found(digraph.num_vertices());
        for (int i{0}; i < digraph.num_vertices(); ++i) {
            found[rank(i)] = true;
        }
        for (int i{0}; i < digraph.num_vertices(); ++i) {
            if (!found[i]) {
                std::cerr << "No vertex with rank " + i;
                return false;
            }
        }

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            for (Directed_edge e : digraph.adjacent(v)) {
                int w = e.to();
                if (rank(v) > rank(w)) {
                    std::cerr << v << "-" << w << ": rank(" << v << ") = " << rank(v) << ", rank(" << w << ") = " << rank(w) << "\n";
                    return false;
                }
            }
        }

        int r{0};
        for (auto v : order()) {
            if (rank(v) != r) {
                std::cerr << "_order() and rank() inconsistent";
                return false;
            }
            ++r;
        }
    }

    return true;
}

void Topological_x::_validate_vertex(int v)
{
    auto num_vertices = _rank.size();
    if (v < 0 || v >= num_vertices) {
        throw utility::Index_out_of_bounds_exception{"vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(num_vertices - 1)};
    }
}
