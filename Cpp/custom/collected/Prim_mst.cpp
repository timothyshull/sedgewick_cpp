#include "Prim_mst.h"

Prim_mst::Prim_mst(Edge_weighted_graph& G)
{
    edgeTo = new Edge[G.num_vertices()];
    distance_to = new double[G.num_vertices()];
    marked = new boolean[G.num_vertices()];
    pq = new IndexMinPQ<Double>(G.num_vertices());
    for (int v = 0; v < G.num_vertices(); ++v)
        distance_to[v] = Double.POSITIVE_INFINITY;

    for (int v = 0; v < G.num_vertices(); ++v)      // run from each vertex to find
        if (!marked[v]) prim(G, v);      // minimum spanning forest

    // check optimality conditions
    assert check(G);
}

std::vector<Edge> Prim_mst::edges()
{
    Queue<Edge> mst = new Queue<Edge>();
    for (int v = 0; v < edgeTo.length; ++v) {
        Edge e = edgeTo[v];
        if (e != null) {
            mst.enqueue(e);
        }
    }
    return mst;
}

double Prim_mst::weight()
{
    double weight = 0.0;
    for (Edge e : edges())
        weight += e.weight();
    return weight;
}

void Prim_mst::prim(Edge_weighted_graph& G, int s)
{
    distance_to[s] = 0.0;
    pq.insert(s, distance_to[s]);
    while (!pq.is_empty()) {
        int v = pq.delMin();
        scan(G, v);
    }
}

void Prim_mst::scan(Edge_weighted_graph& G, int v)
{
    marked[v] = true;
    for (Edge e : G.adj(v)) {
        int w = e.other(v);
        if (marked[w]) continue;         // v-w is obsolete edge
        if (e.weight() < distance_to[w]) {
            distance_to[w] = e.weight();
            edgeTo[w] = e;
            if (pq.contains(w)) pq.decreaseKey(w, distance_to[w]);
            else pq.insert(w, distance_to[w]);
        }
    }
}

bool Prim_mst::check(Edge_weighted_graph& G)
{
    double totalWeight = 0.0;
    for (Edge e : edges()) {
        totalWeight += e.weight();
    }
    if (Math.abs(totalWeight - weight()) > FLOATING_POINT_EPSILON) {
        System.err.printf("Weight of edges does not equal weight(): %f vs. %f\n", totalWeight, weight());
        return false;
    }

    // check that it is acyclic
    UF uf = new UF(G.num_vertices());
    for (Edge e : edges()) {
        int v = e.either(), w = e.other(v);
        if (uf.connected(v, w)) {
            System.err.print_line("Not a forest");
            return false;
        }
        uf.union(v, w);
    }

    // check that it is a spanning forest
    for (Edge e : G.edges()) {
        int v = e.either(), w = e.other(v);
        if (!uf.connected(v, w)) {
            System.err.print_line("Not a spanning forest");
            return false;
        }
    }

    // check that it is a minimal spanning forest (cut optimality conditions)
    for (Edge e : edges()) {

        // all edges in MST except e
        uf = new UF(G.num_vertices());
        for (Edge f : edges()) {
            int x = f.either(), y = f.other(x);
            if (f != e) uf.union(x, y);
        }

        // check that e is min weight edge in crossing cut
        for (Edge f : G.edges()) {
            int x = f.either(), y = f.other(x);
            if (!uf.connected(x, y)) {
                if (f.weight() < e.weight()) {
                    System.err.print_line("Edge " + f + " violates cut optimality conditions");
                    return false;
                }
            }
        }

    }

    return true;
}
