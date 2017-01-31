#include "Nonrecursive_directed_dfs.h"
#include "Stack.h"

Nonrecursive_directed_dfs::Nonrecursive_directed_dfs(Digraph& digraph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices()))
{
    std::vector<std::vector<int>::iterator> adj;
    adj.reserve(static_cast<std::vector<std::vector<int>::iterator>::size_type>(digraph.num_vertices()));
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        adj[v] = digraph.adjacent(v).begin();
    }

    Stack<int> stack;
    _marked[source] = true;
    stack.push(source);
    while (!stack.is_empty()) {
        int v = stack.peek();
        if (adj[v] != digraph.adjacent(v).end()) {
            auto it = adj[v];
            ++it;
            int w = *it;
            // Std_out::printf("_check %d\_size", w);
            if (!_marked[w]) {
                // discovered vertex w for the first time
                _marked[w] = true;
                // _edge_to[w] = v;
                stack.push(w);
                // Std_out::printf("dfs(%d)\_size", w);
            }
        } else {
            // Std_out::printf("%d done\_size", v);
            stack.pop();
        }
    }
}

