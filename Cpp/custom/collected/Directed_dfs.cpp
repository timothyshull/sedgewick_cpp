#include "Directed_dfs.h"

Directed_dfs::Directed_dfs(Digraph& G, int s)
{
    marked = new boolean[G.V()];
    dfs(G, s);
}

Directed_dfs::Directed_dfs(Digraph& G, std::vector<int>& sources)
{
    marked = new boolean[G.V()];
    for (int v : sources) {
        if (!marked[v]) { dfs(G, v); }
    }
}

bool Directed_dfs::marked(int v)
{
    return marked[v];
}

int Directed_dfs::count()
{
    return count;
}

void Directed_dfs::dfs(Digraph& G, int v)
{
    count++;
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) { dfs(G, w); }
    }
}
