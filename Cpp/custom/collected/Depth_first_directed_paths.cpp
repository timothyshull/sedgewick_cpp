#include "Depth_first_directed_paths.h"

Depth_first_directed_paths::Depth_first_directed_paths(Digraph& G, int s)
{
    marked = new boolean[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    this.s = s;
    dfs(G, s);
}

bool Depth_first_directed_paths::has_path_to(int v)
{
    return marked[v];
}

std::vector<int> Depth_first_directed_paths::path_to(int v)
{
    if (!has_path_to(v)) { return null; }
    Stack <Integer> path = new Stack<Integer>();
    for (int x{v}; x != s; x = edgeTo[x]) {
        path.push(x);
    }
    path.push(s);
    return path;
}

void Depth_first_directed_paths::dfs(Digraph& G, int v)
{
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}
