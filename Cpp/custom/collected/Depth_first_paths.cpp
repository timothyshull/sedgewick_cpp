#include "Depth_first_paths.h"

Depth_first_paths::Depth_first_paths(Digraph& G, int s)
{
    this.s = s;
    edgeTo = new int[G.num_vertices()];
    marked = new boolean[G.num_vertices()];
    dfs(G, s);
}

bool Depth_first_paths::has_path_to(int v)
{
    return marked[v];
}

std::vector<int> Depth_first_paths::path_to(int v)
{
    if (!has_path_to(v)) return null;
    Stack<Integer> path = new Stack<Integer>();
    for (int x = v; x != s; x = edgeTo[x])
        path.push(x);
    path.push(s);
    return path;
}

void Depth_first_paths::dfs(Digraph& G, int v)
{
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}
