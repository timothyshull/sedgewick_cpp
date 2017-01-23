#include "Bipartite.h"

Bipartite::Bipartite(Graph& G)
{
    isBipartite = true;
    color = new boolean[G.V()];
    marked = new boolean[G.V()];
    edgeTo = new int[G.V()];

    for (int v = 0; v < G.V(); v++) {
        if (!marked[v]) {
            dfs(G, v);
        }
    }
    assert check(G);
}

bool Bipartite::isBipartite()
{
    return isBipartite;
}

bool Bipartite::color(int v)
{
    if (!isBipartite) {
        throw new UnsupportedOperationException("Graph is not bipartite");
    }
    return color[v];
}

std::vector<int> Bipartite::oddCycle()
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
            isBipartite = false;
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
    if (isBipartite) {
        for (int v = 0; v < G.V(); v++) {
            for (int w : G.adj(v)) {
                if (color[v] == color[w]) {
                    System.err.printf("edge %d-%d with %d and %d in same side of bipartition\n", v, w, v, w);
                    return false;
                }
            }
        }
    }

        // graph has an odd-length cycle
    else {
        // verify cycle
        int first = -1, last = -1;
        for (int v : oddCycle()) {
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
