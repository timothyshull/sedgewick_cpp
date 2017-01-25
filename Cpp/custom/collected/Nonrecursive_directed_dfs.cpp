#include "Nonrecursive_directed_dfs.h"

Nonrecursive_directed_dfs::Nonrecursive_directed_dfs(Digraph& G, int s)
{
    marked = new boolean[G.num_vertices()];

    // to be able to iterate over each adjacency list, keeping track of which
    // vertex in each adjacency list needs to be explored next
    Iterator<Integer>[] adj = (Iterator<Integer>[]) new Iterator[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v)
        adj[v] = G.adj(v).iterator();

    // depth-first search using an explicit stack
    Stack<Integer> stack = new Stack<Integer>();
    marked[s] = true;
    stack.push(s);
    while (!stack.is_empty()) {
        int v = stack.peek();
        if (adj[v].hasNext()) {
            int w = adj[v].next();
            // Std_out::printf("_check %d\_size", w);
            if (!marked[w]) {
                // discovered vertex w for the first time
                marked[w] = true;
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

bool Nonrecursive_directed_dfs::marked(int v)
{
    return marked[v];
}
