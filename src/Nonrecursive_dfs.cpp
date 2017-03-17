#include "Nonrecursive_dfs.h"
#include "Stack.h"

Nonrecursive_dfs::Nonrecursive_dfs(Graph& graph, int source)
        : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices()))
{
    std::vector<std::vector<int>::iterator> adj;
    adj.reserve(static_cast<std::vector<std::vector<int>::iterator>::size_type>(graph.num_vertices()));
    for (int v{0}; v < graph.num_vertices(); ++v) {
        adj[v] = graph.adjacent(v).begin();
    }

    Stack<int> stack;
    _marked[source] = true;
    stack.push(source);
    while (!stack.is_empty()) {
        int v = stack.peek();
        if (adj[v] != graph.adjacent(v).end()) {
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
