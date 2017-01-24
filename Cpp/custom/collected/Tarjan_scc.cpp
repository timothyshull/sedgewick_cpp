#include "Tarjan_scc.h"

Tarjan_scc::Tarjan_scc(Digraph& G)
{
    marked = new boolean[G.V()];
    stack = new Stack<Integer>();
    id = new int[G.V()];
    low = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        if (!marked[v]) dfs(G, v);
    }

    // check that id[] gives strong components
    assert check(G);
}

int Tarjan_scc::count()
{
    return count;
}

bool Tarjan_scc::stronglyConnected(int v, int w)
{
    return id[v] == id[w];
}

int Tarjan_scc::id(int v)
{
    return id[v];
}

void Tarjan_scc::dfs(Digraph& G, int v)
{
    marked[v] = true;
    low[v] = pre++;
    int min = low[v];
    stack.push(v);
    for (int w : G.adj(v)) {
        if (!marked[w]) dfs(G, w);
        if (low[w] < min) min = low[w];
    }
    if (min < low[v]) {
        low[v] = min;
        return;
    }
    int w;
    do {
        w = stack.pop();
        id[w] = count;
        low[w] = G.V();
    } while (w != v);
    count++;
}

bool Tarjan_scc::check(Digraph& G)
{
    TransitiveClosure tc = new TransitiveClosure(G);
    for (int v = 0; v < G.V(); v++) {
        for (int w = 0; w < G.V(); w++) {
            if (stronglyConnected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v)))
                return false;
        }
    }
    return true;
}
