#include "Cycle.h"

Cycle::Cycle(Graph& G)
{
    if (hasSelfLoop(G)) { return; }
    if (hasParallelEdges(G)) { return; }
    marked = new boolean[G.V()];
    edgeTo = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        if (!marked[v]) {
            dfs(G, -1, v);
        }
    }
}

bool Cycle::hasCycle()
{
    return cycle != null;
}

std::vector<int> Cycle::cycle()
{
    return cycle;
}

bool Cycle::hasSelfLoop(Graph& G)
{
    for (int v = 0; v < G.V(); v++) {
        for (int w : G.adj(v)) {
            if (v == w) {
                cycle = new Stack<Integer>();
                cycle.push(v);
                cycle.push(v);
                return true;
            }
        }
    }
    return false;
}

bool Cycle::hasParallelEdges(Graph& G)
{
    marked = new boolean[G.V()];

    for (int v = 0; v < G.V(); v++) {

        // check for parallel edges incident to v
        for (int w : G.adj(v)) {
            if (marked[w]) {
                cycle = new Stack<Integer>();
                cycle.push(v);
                cycle.push(w);
                cycle.push(v);
                return true;
            }
            marked[w] = true;
        }

        // reset so marked[v] = false for all v
        for (int w : G.adj(v)) {
            marked[w] = false;
        }
    }
    return false;
}

void Cycle::dfs(Graph& G, int u, int v)
{
    marked[v] = true;
    for (int w : G.adj(v)) {

        // short circuit if cycle already found
        if (cycle != null) { return; }

        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, v, w);
        }

            // check for cycle (but disregard reverse of edge leading to v)
        else if (w != u) {
            cycle = new Stack<Integer>();
            for (int x = v; x != w; x = edgeTo[x]) {
                cycle.push(x);
            }
            cycle.push(w);
            cycle.push(v);
        }
    }
}
