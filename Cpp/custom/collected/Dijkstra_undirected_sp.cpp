#include "Dijkstra_undirected_sp.h"

Dijkstra_undirected_sp::Dijkstra_undirected_sp(Edge_weighted_digraph& G, int s)
{
    for (Edge e : G.edges()) {
        if (e.weight() < 0) {
            throw new IllegalArgumentException("edge " + e + " has negative weight");
        }
    }

    distTo = new double[G.V()];
    edgeTo = new Edge[G.V()];
    for (int v = 0; v < G.V(); v++) {
        distTo[v] = Double.POSITIVE_INFINITY;
    }
    distTo[s] = 0.0;

    // relax vertices in order of distance from s
    pq = new IndexMinPQ<Double>(G.V());
    pq.insert(s, distTo[s]);
    while (!pq.isEmpty()) {
        int v = pq.delMin();
        for (Edge e : G.adj(v)) {
            relax(e, v);
        }
    }

    // check optimality conditions
    assert check(G, s);
}

double Dijkstra_undirected_sp::distTo(int v)
{
    return distTo[v];
}

bool Dijkstra_undirected_sp::hasPathTo(int v)
{
    return distTo[v] < Double.POSITIVE_INFINITY;
}

std::vector<Directed_edge> Dijkstra_undirected_sp::pathTo(int v)
{
    if (!hasPathTo(v)) { return null; }
    Stack<Edge> path = new Stack<Edge>();
    int x = v;
    for (Edge e = edgeTo[v]; e != null; e = edgeTo[x]) {
        path.push(e);
        x = e.other(x);
    }
    return path;
}

void Dijkstra_undirected_sp::relax(Directed_edge& e)
{
    int w = e.other(v);
    if (distTo[w] > distTo[v] + e.weight()) {
        distTo[w] = distTo[v] + e.weight();
        edgeTo[w] = e;
        if (pq.contains(w)) { pq.decreaseKey(w, distTo[w]); }
        else { pq.insert(w, distTo[w]); }
    }
}

bool Dijkstra_undirected_sp::check(Edge_weighted_digraph& G, int s)
{
    for (Edge e : G.edges()) {
        if (e.weight() < 0) {
            System.err.println("negative edge weight detected");
            return false;
        }
    }

    // check that distTo[v] and edgeTo[v] are consistent
    if (distTo[s] != 0.0 || edgeTo[s] != null) {
        System.err.println("distTo[s] and edgeTo[s] inconsistent");
        return false;
    }
    for (int v = 0; v < G.V(); v++) {
        if (v == s) { continue; }
        if (edgeTo[v] == null && distTo[v] != Double.POSITIVE_INFINITY) {
            System.err.println("distTo[] and edgeTo[] inconsistent");
            return false;
        }
    }

    // check that all edges e = v-w satisfy distTo[w] <= distTo[v] + e.weight()
    for (int v = 0; v < G.V(); v++) {
        for (Edge e : G.adj(v)) {
            int w = e.other(v);
            if (distTo[v] + e.weight() < distTo[w]) {
                System.err.println("edge " + e + " not relaxed");
                return false;
            }
        }
    }

    // check that all edges e = v-w on SPT satisfy distTo[w] == distTo[v] + e.weight()
    for (int w = 0; w < G.V(); w++) {
        if (edgeTo[w] == null) { continue; }
        Edge e = edgeTo[w];
        if (w != e.either() && w != e.other(e.either())) { return false; }
        int v = e.other(w);
        if (distTo[v] + e.weight() != distTo[w]) {
            System.err.println("edge " + e + " on shortest path not tight");
            return false;
        }
    }
    return true;
}
