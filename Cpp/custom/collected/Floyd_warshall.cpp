#include "Floyd_warshall.h"

Floyd_warshall::Floyd_warshall(Adj_matrix_edge_weighted_digraph& G)
{
    int V = G.num_vertices();
    distance_to = new double[V][V];
    edgeTo = new Directed_edge[V][V];

    // initialize distances to infinity
    for (int v = 0; v < V; ++v) {
        for (int w = 0; w < V; ++w) {
            distance_to[v][w] = Double.POSITIVE_INFINITY;
        }
    }

    // initialize distances using edge-weighted digraph's
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (Directed_edge e : G.adj(v)) {
            distance_to[e.from()][e.to()] = e.weight();
            edgeTo[e.from()][e.to()] = e;
        }
        // in case of self-loops
        if (distance_to[v][v] >= 0.0) {
            distance_to[v][v] = 0.0;
            edgeTo[v][v] = null;
        }
    }

    // Floyd-Warshall updates
    for (int i = 0; i < V; ++i) {
        // compute shortest paths using only 0, 1, ..., i as intermediate vertices
        for (int v = 0; v < V; ++v) {
            if (edgeTo[v][i] == null) { continue; }  // optimization
            for (int w = 0; w < V; ++w) {
                if (distance_to[v][w] > distance_to[v][i] + distance_to[i][w]) {
                    distance_to[v][w] = distance_to[v][i] + distance_to[i][w];
                    edgeTo[v][w] = edgeTo[i][w];
                }
            }
            // check for negative cycle
            if (distance_to[v][v] < 0.0) {
                hasNegativeCycle = true;
                return;
            }
        }
    }
    assert check(G);
}

bool Floyd_warshall::hasNegativeCycle()
{
    return hasNegativeCycle;
}

std::vector<Directed_edge> Floyd_warshall::negativeCycle()
{
    for (int v = 0; v < distance_to.length; ++v) {
        // negative cycle in v's predecessor graph
        if (distance_to[v][v] < 0.0) {
            int V = edgeTo.length;
            Edge_weighted_digraph spt = new Edge_weighted_digraph(V);
            for (int w = 0; w < V; ++w) {
                if (edgeTo[v][w] != null) {
                    spt.add_edge(edgeTo[v][w]);
                }
            }
            EdgeWeightedDirectedCycle finder = new EdgeWeightedDirectedCycle(spt);
            assert
            finder.has_cycle();
            return finder.cycle();
        }
    }
    return null;
}

bool Floyd_warshall::hasPath(int s, int t)
{
    return distance_to[s][t] < Double.POSITIVE_INFINITY;
}

double Floyd_warshall::dist(int s, int t)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    return distance_to[s][t];
}

std::vector<Directed_edge> Floyd_warshall::path(int s, int t)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    if (!hasPath(s, t)) { return null; }
    Stack <Directed_edge> path = new Stack<Directed_edge>();
    for (Directed_edge e = edgeTo[s][t]; e != null; e = edgeTo[s][e.from()]) {
        path.push(e);
    }
    return path;
}

bool Floyd_warshall::check(Adj_matrix_edge_weighted_digraph& G)
{
    if (!hasNegativeCycle()) {
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (Directed_edge e : G.adj(v)) {
                int w = e.to();
                for (int i = 0; i < G.num_vertices(); ++i) {
                    if (distance_to[i][w] > distance_to[i][v] + e.weight()) {
                        System.err.print_line("edge " + e + " is eligible");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
