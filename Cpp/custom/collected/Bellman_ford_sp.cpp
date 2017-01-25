#include "Bellman_ford_sp.h"

Bellman_ford_sp::Bellman_ford_sp(Edge_weighted_digraph, int)
{
    distance_to = new double[G.num_vertices()];
    edgeTo = new Directed_edge[G.num_vertices()];
    onQueue = new boolean[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        distance_to[v] = Double.POSITIVE_INFINITY;
    }
    distance_to[s] = 0.0;

    // Bellman-Ford algorithm
    queue = new Queue<Integer>();
    queue.enqueue(s);
    onQueue[s] = true;
    while (!queue.is_empty() && !hasNegativeCycle()) {
        int v = queue.dequeue();
        onQueue[v] = false;
        relax(G, v);
    }

    assert check(G, s);
}

bool Bellman_ford_sp::hasNegativeCycle()
{
    return cycle != null;
}

std::vector<Directed_edge> Bellman_ford_sp::negativeCycle()
{
    return cycle;
}

double Bellman_ford_sp::distance_to(int)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    return distance_to[v];
}

bool Bellman_ford_sp::has_path_to(int)
{
    return distance_to[v] < Double.POSITIVE_INFINITY;
}

std::vector<Directed_edge> Bellman_ford_sp::path_to(int)
{
    if (hasNegativeCycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    if (!has_path_to(v)) { return null; }
    Stack<Directed_edge> path = new Stack<Directed_edge>();
    for (Directed_edge e = edgeTo[v]; e != null; e = edgeTo[e.from()]) {
        path.push(e);
    }
    return path;
}

void Bellman_ford_sp::relax(Edge_weighted_digraph, int)
{
    for (Directed_edge e : G.adj(v)) {
        int w = e.to();
        if (distance_to[w] > distance_to[v] + e.weight()) {
            distance_to[w] = distance_to[v] + e.weight();
            edgeTo[w] = e;
            if (!onQueue[w]) {
                queue.enqueue(w);
                onQueue[w] = true;
            }
        }
        if (cost++ % G.num_vertices() == 0) {
            findNegativeCycle();
            if (hasNegativeCycle()) { return; }  // found a negative cycle
        }
    }
}

void Bellman_ford_sp::findNegativeCycle()
{
    int num_vertices = edgeTo.length;
    Edge_weighted_digraph spt = new Edge_weighted_digraph(V);
    for (int v = 0; v < V; ++v) {
        if (edgeTo[v] != null) {
            spt.add_edge(edgeTo[v]);
        }
    }

    Edge_weighted_directed_cycle finder = new Edge_weighted_directed_cycle(spt);
    cycle = finder.cycle();
}

bool Bellman_ford_sp::check(Edge_weighted_digraph, int)
{
    // has a negative cycle
    if (hasNegativeCycle()) {
        double weight = 0.0;
        for (Directed_edge e : negativeCycle()) {
            weight += e.weight();
        }
        if (weight >= 0.0) {
            System.err.print_line("error: weight of negative cycle = " + weight);
            return false;
        }
    }

        // no negative cycle reachable from source
    else {

        // check that _distance_to[v] and edgeTo[v] are consistent
        if (distance_to[s] != 0.0 || edgeTo[s] != null) {
            System.err.print_line("distanceTo[s] and edgeTo[s] inconsistent");
            return false;
        }
        for (int v = 0; v < G.num_vertices(); ++v) {
            if (v == s) { continue; }
            if (edgeTo[v] == null && distance_to[v] != Double.POSITIVE_INFINITY) {
                System.err.print_line("_distance_to[] and edgeTo[] inconsistent");
                return false;
            }
        }

        // check that all edges e = v->w satisfy _distance_to[w] <= _distance_to[v] + e.weight()
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (Directed_edge e : G.adj(v)) {
                int w = e.to();
                if (distance_to[v] + e.weight() < distance_to[w]) {
                    System.err.print_line("edge " + e + " not relaxed");
                    return false;
                }
            }
        }

        // check that all edges e = v->w on SPT satisfy _distance_to[w] == _distance_to[v] + e.weight()
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
    }

    Std_out::print_line("Satisfies optimality conditions");
    Std_out::print_line();
    return true;
}
