#include "Connected_component.h"

Connected_component::Connected_component(Graph& G)
{
    marked = new boolean[G.num_vertices()];
    id = new int[G.num_vertices()];
    size = new int[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (!marked[v]) {
            dfs(G, v);
            ++count;
        }
    }
}

int Connected_component::id(int v)
{
    return id[v];
}

int Connected_component::size(int v)
{
    return size[id[v]];
}

int Connected_component::count()
{
    return count;
}

bool Connected_component::connected(int v, int w)
{
    return id(v) == id(w);
}

bool Connected_component::areConnected(int v, int w)
{
    return id(v) == id(w);
}

void Connected_component::dfs(Graph& G, int v)
{
    marked[v] = true;
    id[v] = count;
    size[count]++;
    for (int w : G.adj(v)) {
        if (!marked[w]) {
            dfs(G, w);
        }
    }
}
