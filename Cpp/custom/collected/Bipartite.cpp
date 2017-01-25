#include "Bipartite.h"

Bipartite::Bipartite(Graph& G)
{
    is_bipartite = true;
    color = new boolean[G.num_vertices()];
    marked = new boolean[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];

    for (int v = 0; v < G.num_vertices(); ++v) {
        if (!marked[v]) {
            dfs(G, v);
        }
    }
    assert check(G);
}

bool Bipartite::is_bipartite()
{
    return is_bipartite;
}

bool Bipartite::color(int v)
{
    if (!is_bipartite) {
        throw new UnsupportedOperationException("Graph is not bipartite");
    }
    return color[v];
}

std::vector<int> Bipartite::odd_cycle()
{
    return cycle;
}

void Bipartite::dfs(Graph& G, int v)
{
    marked[v] = true;
    for (int w : G.adj(v)) {

        // short circuit if odd-length cycle found
        if (cycle != null) { return; }

        // found uncolored vertex, so recur
        if (!marked[w]) {
            edgeTo[w] = v;
            color[w] = !color[v];
            dfs(G, w);
        }

            // if v-w create an odd-length cycle, find it
        else if (color[w] == color[v]) {
            is_bipartite = false;
            cycle = new Stack<Integer>();
            cycle.push(w);  // don't need this unless you want to include start vertex twice
            for (int x = v; x != w; x = edgeTo[x]) {
                cycle.push(x);
            }
            cycle.push(w);
        }
    }
}

bool Bipartite::check(Graph& G)
{
    if (is_bipartite) {
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (int w : G.adj(v)) {
                if (color[v] == color[w]) {
                    System.err.printf("edge %d-%d with %d and %d in same side of _bipartition\n", v, w, v, w);
                    return false;
                }
            }
        }
    }

        // graph has an odd-length cycle
    else {
        // verify cycle
        int first = -1, last = -1;
        for (int v : odd_cycle()) {
            if (first == -1) { first = v; }
            last = v;
        }
        if (first != last) {
            System.err.printf("cycle begins with %d and ends with %d\n", first, last);
            return false;
        }
    }

    return true;
}
