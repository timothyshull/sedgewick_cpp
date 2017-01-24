#include "Nonrecursive_dfs.h"

Nonrecursive_dfs::Nonrecursive_dfs(Graph& G, int s)
{
    marked = new boolean[G.V()];

    // to be able to iterate over each adjacency list, keeping track of which
    // vertex in each adjacency list needs to be explored next
    Iterator<Integer>[] adj = (Iterator<Integer>[]) new Iterator[G.V()];
    for (int v = 0; v < G.V(); v++)
        adj[v] = G.adj(v).iterator();

    // depth-first search using an explicit stack
    Stack<Integer> stack = new Stack<Integer>();
    marked[s] = true;
    stack.push(s);
    while (!stack.isEmpty()) {
        int v = stack.peek();
        if (adj[v].hasNext()) {
            int w = adj[v].next();
            // StdOut.printf("check %d\n", w);
            if (!marked[w]) {
                // discovered vertex w for the first time
                marked[w] = true;
                // edgeTo[w] = v;
                stack.push(w);
                // StdOut.printf("dfs(%d)\n", w);
            }
        } else {
            // StdOut.printf("%d done\n", v);
            stack.pop();
        }
    }
}

bool Nonrecursive_dfs::marked(int v)
{
    return marked[v];
}
