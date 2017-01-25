#include "Cycle.h"

Cycle::Cycle(Graph& G)
{
    if (hasSelfLoop(G)) { return; }
    if (hasParallelEdges(G)) { return; }
    marked = new boolean[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (!marked[v]) {
            dfs(G, -1, v);
        }
    }
}

bool Cycle::has_cycle()
{
    return cycle != null;
}

std::vector<int> Cycle::cycle()
{
    return cycle;
}

bool Cycle::hasSelfLoop(Graph& G)
{
    for (int v{0}; v < G.num_vertices(); ++v) {
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
    marked = new boolean[G.num_vertices()];

    for (int v{0}; v < G.num_vertices(); ++v) {

        // _check for parallel edges incident to v
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

        // reset so _marked[v] = false for all v
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

        // short circuit if _cycle already found
        if (cycle != null) { return; }

        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, v, w);
        }

            // _check for _cycle (but disregard reverse of edge leading to v)
        else if (w != u) {
            cycle = new Stack<Integer>();
            for (int x{v}; x != w; x = edgeTo[x]) {
                cycle.push(x);
            }
            cycle.push(w);
            cycle.push(v);
        }
    }
}
