#include "Dijkstra_sp.h"

Dijkstra_sp::Dijkstra_sp(Edge_weighted_digraph& G, int s)
{
    for (Directed_edge e : G.edges()) {
        if (e.weight() < 0) {
            throw utility::Illegal_argument_exception("edge " + e + " has negative weight");
        }
    }

    distance_to = new double[G.num_vertices()];
    edgeTo = new Directed_edge[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        distance_to[v] = Double.POSITIVE_INFINITY;
    }
    distance_to[s] = 0.0;

    // relax vertices in order of distance from s
    pq = new IndexMinPQ<Double>(G.num_vertices());
    pq.insert(s, distance_to[s]);
    while (!pq.is_empty()) {
        int v = pq.delMin();
        for (Directed_edge e : G.adj(v)) {
            relax(e);
        }
    }

    // check optimality conditions
    assert check(G, s);
}

double Dijkstra_sp::distance_to(int v)
{
    return distance_to[v];
}

bool Dijkstra_sp::has_path_to(int v)
{
    return distance_to[v] < Double.POSITIVE_INFINITY;
}

std::vector<Directed_edge> Dijkstra_sp::path_to(int v)
{
    if (!has_path_to(v)) { return null; }
    Stack<Directed_edge> path = new Stack<Directed_edge>();
    for (Directed_edge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
        path.push(e);
    }
    return path;
}

void Dijkstra_sp::relax(Directed_edge& e)
{
    int v = e.from(), w = e.to();
    if (distance_to[w] > distance_to[v] + e.weight()) {
        distance_to[w] = distance_to[v] + e.weight();
        edgeTo[w] = e;
        if (pq.contains(w)) { pq.decreaseKey(w, distance_to[w]); }
        else { pq.insert(w, distance_to[w]); }
    }
}

bool Dijkstra_sp::check(Edge_weighted_digraph& G, int s)
{
    for (Directed_edge e : G.edges()) {
        if (e.weight() < 0) {
            System.err.print_line("negative edge weight detected");
            return false;
        }
    }

    // check that distance_to[v] and edgeTo[v] are consistent
    if (distance_to[s] != 0.0 || edgeTo[s] != null) {
        System.err.print_line("distance_to[s] and edgeTo[s] inconsistent");
        return false;
    }
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (v == s) { continue; }
        if (edgeTo[v] == null && distance_to[v] != Double.POSITIVE_INFINITY) {
            System.err.print_line("distance_to[] and edgeTo[] inconsistent");
            return false;
        }
    }

    // check that all edges e = v->w satisfy distance_to[w] <= distance_to[v] + e.weight()
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (Directed_edge e : G.adj(v)) {
            int w = e.to();
            if (distance_to[v] + e.weight() < distance_to[w]) {
                System.err.print_line("edge " + e + " not relaxed");
                return false;
            }
        }
    }

    // check that all edges e = v->w on SPT satisfy distance_to[w] == distance_to[v] + e.weight()
    for (int w = 0; w < G.num_vertices(); ++w) {
        if (edgeTo[w] == null) { continue; }
        Directed_edge e = edgeTo[w];
        int v = e.from();
        if (w != e.to()) { return false; }
        if (distance_to[v] + e.weight() != distance_to[w]) {
            System.err.print_line("edge " + e + " on shortest path not tight");
            return false;
        }
    }
    return true;
}
