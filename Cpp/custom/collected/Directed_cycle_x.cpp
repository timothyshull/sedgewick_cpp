#include <deque>
#include "Directed_cycle_x.h"
#include "Queue.h"
#include "Stack.h"

Directed_cycle_x::Directed_cycle_x(Digraph& digraph)
{
    std::vector<int> indegree;
    indegree.reserve(static_cast<std::vector<int>::size_type>(digraph.num_vertices()));
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        indegree[v] = digraph.indegree(v);
    }

    Queue<int> queue;
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (indegree[v] == 0) { queue.enqueue(v); }
    }

    for (int j{0}; !queue.is_empty(); ++j) {
        int v = queue.dequeue();
        for (auto w : digraph.adjacent(v)) {
            indegree[w]--;
            if (indegree[w] == 0) { queue.enqueue(w); }
        }
    }

    std::vector<int> edge_to;
    edge_to.reserve(static_cast<std::vector<int>::size_type>(digraph.num_vertices()));
    int root{-1};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (indegree[v] == 0) { continue; }
        else { root = v; }
        for (auto w : digraph.adjacent(v)) {
            if (indegree[w] > 0) {
                edge_to[w] = v;
            }
        }
    }

    if (root != -1) {
        std::deque<bool> visited{static_cast<std::deque<bool>::size_type>(digraph.num_vertices())};
        while (!visited[root]) {
            visited[root] = true;
            root = edge_to[root];
        }

        _cycle = Stack<int>{};
        int v = root;
        do {
            _cycle.push(v);
            v = edge_to[v];
        } while (v != root);
        _cycle.push(root);
    }

    utility::alg_assert(_check(), "Directed_cycle_x invariant check failed after construction");
}

bool Directed_cycle_x::_check()
{
    if (has_cycle()) {
        int first{-1};
        int last{-1};
        for (auto v : _cycle()) {
            if (first == -1) { first = v; }
            last = v;
        }
        if (first != last) {
            std::cerr << "_cycle begins with " << first << " and ends with " << last << "\n";
            return false;
        }
    }

    return true;
}
