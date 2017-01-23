#include "Floyd_warshall.h"

Floyd_warshall::Floyd_warshall(Adj_matrix_edge_weighted_digraph& G)
{
    int V = G.V();
    distTo = new double[V][V];
    edgeTo = new DirectedEdge[V][V];

    // initialize distances to infinity
    for (int v = 0; v < V; v++) {
        for (int w = 0; w < V; w++) {
            distTo[v][w] = Double.POSITIVE_INFINITY;
        }
    }

    // initialize distances using edge-weighted digraph's
    for (int v = 0; v < G.V(); v++) {
        for (DirectedEdge e : G.adj(v)) {
            distTo[e.from()][e.to()] = e.weight();
            edgeTo[e.from()][e.to()] = e;
        }
        // in case of self-loops
        if (distTo[v][v] >= 0.0) {
            distTo[v][v] = 0.0;
            edgeTo[v][v] = null;
        }
    }

    // Floyd-Warshall updates
    for (int i = 0; i < V; i++) {
        // compute shortest paths using only 0, 1, ..., i as intermediate vertices
        for (int v = 0; v < V; v++) {
            if (edgeTo[v][i] == null) { continue; }  // optimization
            for (int w = 0; w < V; w++) {
                if (distTo[v][w] > distTo[v][i] + distTo[i][w]) {
                    distTo[v][w] = distTo[v][i] + distTo[i][w];
                    edgeTo[v][w] = edgeTo[i][w];
                }
            }
            // check for negative cycle
            if (distTo[v][v] < 0.0) {
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
    for (int v = 0; v < distTo.length; v++) {
        // negative cycle in v's predecessor graph
        if (distTo[v][v] < 0.0) {
            int V = edgeTo.length;
            EdgeWeightedDigraph spt = new EdgeWeightedDigraph(V);
            for (int w = 0; w < V; w++) {
                if (edgeTo[v][w] != null) {
                    spt.addEdge(edgeTo[v][w]);
                }
            }
            EdgeWeightedDirectedCycle finder = new EdgeWeightedDirectedCycle(spt);
            assert
            finder.hasCycle();
            return finder.cycle();
        }
    }
    return null;
}

bool Floyd_warshall::hasPath(int s, int t)
{
    return distTo[s][t] < Double.POSITIVE_INFINITY;
}

double Floyd_warshall::dist(int s, int t)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    return distTo[s][t];
}

std::vector<Directed_edge> Floyd_warshall::path(int s, int t)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    if (!hasPath(s, t)) { return null; }
    Stack <DirectedEdge> path = new Stack<DirectedEdge>();
    for (DirectedEdge e = edgeTo[s][t]; e != null; e = edgeTo[s][e.from()]) {
        path.push(e);
    }
    return path;
}

bool Floyd_warshall::check(Adj_matrix_edge_weighted_digraph& G)
{
    if (!hasNegativeCycle()) {
        for (int v = 0; v < G.V(); v++) {
            for (DirectedEdge e : G.adj(v)) {
                int w = e.to();
                for (int i = 0; i < G.V(); i++) {
                    if (distTo[i][w] > distTo[i][v] + e.weight()) {
                        System.err.println("edge " + e + " is eligible");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
