#include "Depth_first_search.h"

Depth_first_search::Depth_first_search(Graph& G, int s)
{
    marked = new boolean[G.num_vertices()];
    dfs(G, s);
}

bool Depth_first_search::marked(int v)
{
    return marked[v];
}

int Depth_first_search::count()
{
    return count;
}

void Depth_first_search::dfs(Graph& G, int v)
{
    ++count;
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) {
            dfs(G, w);
        }
    }
}
