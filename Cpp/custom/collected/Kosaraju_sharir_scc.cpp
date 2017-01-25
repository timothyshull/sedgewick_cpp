#include "Kosaraju_sharir_scc.h"

Kosaraju_sharir_scc::Kosaraju_sharir_scc(Digraph& G)
{
    DepthFirstOrder dfs = new DepthFirstOrder(G.reverse());

    // run DFS on G, using reverse postorder to guide calculation
    marked = new boolean[G.num_vertices()];
    id = new int[G.num_vertices()];
    for (int v : dfs.reversePost()) {
        if (!marked[v]) {
            dfs(G, v);
            ++count;
        }
    }

    // check that id[] gives strong components
    assert check(G);
}

int Kosaraju_sharir_scc::count()
{
    return count;
}

bool Kosaraju_sharir_scc::stronglyConnected(int v, int w)
{
    return id[v] == id[w];
}

int Kosaraju_sharir_scc::id(int v)
{
    return id[v];
}

void Kosaraju_sharir_scc::dfs(Digraph& G, int v)
{
    marked[v] = true;
    id[v] = count;
    for (int w : G.adj(v)) {
        if (!marked[w]) { dfs(G, w); }
    }
}

bool Kosaraju_sharir_scc::check(Digraph& G)
{
    TransitiveClosure tc = new TransitiveClosure(G);
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (int w = 0; w < G.num_vertices(); ++w) {
            if (stronglyConnected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v))) {
                return false;
            }
        }
    }
    return true;
}
