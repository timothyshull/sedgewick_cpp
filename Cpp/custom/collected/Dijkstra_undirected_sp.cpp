#include "Dijkstra_undirected_sp.h"

Dijkstra_undirected_sp::Dijkstra_undirected_sp(Edge_weighted_digraph& G, int s)
{
    for (Edge e : G.edges()) {
        if (e.weight() < 0) {
            throw utility::Illegal_argument_exception("edge " + e + " has negative weight");
        }
    }

    distance_to = new double[G.num_vertices()];
    edgeTo = new Edge[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        distance_to[v] = Double.POSITIVE_INFINITY;
    }
    distance_to[s] = 0.0;

    // relax vertices in order of distance from s
    pq = new IndexMinPQ<Double>(G.num_vertices());
    pq.insert(s, distance_to[s]);
    while (!pq.is_empty()) {
        int v = pq.delMin();
        for (Edge e : G.adj(v)) {
            relax(e, v);
        }
    }

    // check optimality conditions
    assert check(G, s);
}

double Dijkstra_undirected_sp::distance_to(int v)
{
    return distance_to[v];
}

bool Dijkstra_undirected_sp::has_path_to(int v)
{
    return distance_to[v] < Double.POSITIVE_INFINITY;
}

std::vector<Directed_edge> Dijkstra_undirected_sp::path_to(int v)
{
    if (!has_path_to(v)) { return null; }
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
    if (distance_to[w] > distance_to[v] + e.weight()) {
        distance_to[w] = distance_to[v] + e.weight();
        edgeTo[w] = e;
        if (pq.contains(w)) { pq.decreaseKey(w, distance_to[w]); }
        else { pq.insert(w, distance_to[w]); }
    }
}

bool Dijkstra_undirected_sp::check(Edge_weighted_digraph& G, int s)
{
    for (Edge e : G.edges()) {
        if (e.weight() < 0) {
            System.err.print_line("negative edge weight detected");
            return false;
        }
    }

    // check that _distance_to[v] and edgeTo[v] are consistent
    if (distance_to[s] != 0.0 || edgeTo[s] != null) {
        System.err.print_line("_distance_to[s] and edgeTo[s] inconsistent");
        return false;
    }
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (v == s) { continue; }
        if (edgeTo[v] == null && distance_to[v] != Double.POSITIVE_INFINITY) {
            System.err.print_line("_distance_to[] and edgeTo[] inconsistent");
            return false;
        }
    }

    // check that all edges e = v-w satisfy _distance_to[w] <= _distance_to[v] + e.weight()
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (Edge e : G.adj(v)) {
            int w = e.other(v);
            if (distance_to[v] + e.weight() < distance_to[w]) {
                System.err.print_line("edge " + e + " not relaxed");
                return false;
            }
        }
    }

    // check that all edges e = v-w on SPT satisfy _distance_to[w] == _distance_to[v] + e.weight()
    for (int w = 0; w < G.num_vertices(); ++w) {
        if (edgeTo[w] == null) { continue; }
        Edge e = edgeTo[w];
        if (w != e.either() && w != e.other(e.either())) { return false; }
        int v = e.other(w);
        if (distance_to[v] + e.weight() != distance_to[w]) {
            System.err.print_line("edge " + e + " on shortest path not tight");
            return false;
        }
    }
    return true;
}
