#include "Floyd_warshall.h"

Floyd_warshall::Floyd_warshall(Adj_matrix_edge_weighted_digraph& G)
{
    int num_vertices = G.num_vertices();
    _distances = new double[V][V];
    _edge_to = new Directed_edge[V][V];

    // initialize distances to infinity
    for (int v = 0; v < V; ++v) {
        for (int w = 0; w < V; ++w) {
            _distances[v][w] = Double.POSITIVE_INFINITY;
        }
    }

    // initialize distances using edge-weighted digraph's
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (Directed_edge e : G.adj(v)) {
            _distances[e.from()][e.to()] = e.weight();
            _edge_to[e.from()][e.to()] = e;
        }
        // in case of self-loops
        if (_distances[v][v] >= 0.0) {
            _distances[v][v] = 0.0;
            _edge_to[v][v] = null;
        }
    }

    // Floyd-Warshall updates
    for (int i = 0; i < V; ++i) {
        // compute shortest paths using only 0, 1, ..., i as intermediate vertices
        for (int v = 0; v < V; ++v) {
            if (_edge_to[v][i] == null) { continue; }  // optimization
            for (int w = 0; w < V; ++w) {
                if (_distances[v][w] > _distances[v][i] + _distances[i][w]) {
                    _distances[v][w] = _distances[v][i] + _distances[i][w];
                    _edge_to[v][w] = _edge_to[i][w];
                }
            }
            // check for negative cycle
            if (_distances[v][v] < 0.0) {
                has_negative_cycle = true;
                return;
            }
        }
    }
    assert check(G);
}

bool Floyd_warshall::has_negative_cycle()
{
    return has_negative_cycle;
}

std::vector<Directed_edge> Floyd_warshall::negative_cycle()
{
    for (int v = 0; v < _distances.length; ++v) {
        // negative cycle in v's predecessor graph
        if (_distances[v][v] < 0.0) {
            int num_vertices = _edge_to.length;
            Edge_weighted_digraph spt = new Edge_weighted_digraph(V);
            for (int w = 0; w < V; ++w) {
                if (_edge_to[v][w] != null) {
                    spt.add_edge(_edge_to[v][w]);
                }
            }
            Edge_weighted_directed_cycle finder = new Edge_weighted_directed_cycle(spt);
            assert
            finder.has_cycle();
            return finder.cycle();
        }
    }
    return null;
}

bool Floyd_warshall::has_path(int s, int t)
{
    return _distances[s][t] < Double.POSITIVE_INFINITY;
}

double Floyd_warshall::distance(int s, int t)
{
    if (has_negative_cycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    return _distances[s][t];
}

std::vector<Directed_edge> Floyd_warshall::path(int s, int t)
{
    if (has_negative_cycle()) {
        throw new UnsupportedOperationException("Negative cost cycle exists");
    }
    if (!has_path(s, t)) { return null; }
    Stack <Directed_edge> path = new Stack<Directed_edge>();
    for (Directed_edge e = _edge_to[s][t]; e != null; e = _edge_to[s][e.from()]) {
        path.push(e);
    }
    return path;
}

bool Floyd_warshall::check(Adj_matrix_edge_weighted_digraph& G)
{
    if (!has_negative_cycle()) {
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (Directed_edge e : G.adj(v)) {
                int w = e.to();
                for (int i = 0; i < G.num_vertices(); ++i) {
                    if (_distances[i][w] > _distances[i][v] + e.weight()) {
                        System.err.print_line("edge " + e + " is eligible");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
