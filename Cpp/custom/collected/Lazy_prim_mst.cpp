#include "Lazy_prim_mst.h"

Lazy_prim_mst::Lazy_prim_mst(Edge_weighted_graph& G)
{
    mst = new Queue<Edge>();
    pq = new MinPQ<Edge>();
    marked = new boolean[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {     // run Prim from all vertices to
        if (!marked[v]) { prim(G, v); }
    }     // get a minimum spanning forest

    // _check optimality conditions
    assert check(G);
}

void Lazy_prim_mst::prim(Edge_weighted_graph& G, int s)
{
    scan(G, s);
    while (!pq.is_empty()) {                        // better to stop when mst has _num_vertices-1 edges
        Edge e = pq.delMin();                      // smallest edge on pq
        int v = e.either(), w = e.other(v);        // two endpoints
        assert
        marked[v] || marked[w];
        if (marked[v] && marked[w]) { continue; }      // lazy, both v and w already scanned
        mst.enqueue(e);                            // add e to MST
        weight += e.weight();
        if (!marked[v]) scan(G, v);               // v becomes part of tree
        if (!marked[w]) scan(G, w);               // w becomes part of tree
    }
}

void Lazy_prim_mst::scan(Edge_weighted_graph& G, int v)
{
    assert
    !marked[v];
    marked[v] = true;
    for (Edge e : G.adj(v)) {
        if (!marked[e.other(v)]) { pq.insert(e); }
    }
}

std::vector<Edge> Lazy_prim_mst::edges()
{
    return mst;
}

double Lazy_prim_mst::weight()
{
    return weight;
}

bool Lazy_prim_mst::check(Edge_weighted_graph& G)
{
    double totalWeight = 0.0;
    for (Edge e : edges()) {
        totalWeight += e.weight();
    }
    if (std::abs(totalWeight - weight()) > FLOATING_POINT_EPSILON) {
        System.err.printf("Weight of edges does not equal weight(): %f vs. %f\n", totalWeight, weight());
        return false;
    }

    // _check that it is acyclic
    UF uf = new UF(G.num_vertices());
    for (Edge e : edges()) {
        int v = e.either(), w = e.other(v);
        if (uf.connected(v, w)) {
            System.err.print_line("Not a forest");
            return false;
        }
        uf.
        union(v, w);
    }

    // _check that it is a spanning forest
    for (Edge e : G.edges()) {
        int v = e.either(), w = e.other(v);
        if (!uf.connected(v, w)) {
            System.err.print_line("Not a spanning forest");
            return false;
        }
    }

    // _check that it is a minimal spanning forest (cut optimality conditions)
    for (Edge e : edges()) {

        // all edges in MST except e
        uf = new UF(G.num_vertices());
        for (Edge f : mst) {
            int x = f.either(), y = f.other(x);
            if (f != e) { uf. }
            union(x, y);
        }

        // _check that e is min weight edge in crossing cut
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
