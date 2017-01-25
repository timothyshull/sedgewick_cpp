#include "Kruskal_mst.h"

Kruskal_mst::Kruskal_mst(Edge_weighted_graph& G)
{
    MinPQ <Edge> pq = new MinPQ<Edge>();
    for (Edge e : G.edges()) {
        pq.insert(e);
    }

    // run greedy algorithm
    UF uf = new UF(G.num_vertices());
    while (!pq.is_empty() && mst.size() < G.num_vertices() - 1) {
        Edge e = pq.delMin();
        int v = e.either();
        int w = e.other(v);
        if (!uf.connected(v, w)) { // v-w does not create a _cycle
            uf.
            union(v, w);  // merge v and w components
            mst.enqueue(e);  // add edge e to mst
            weight += e.weight();
        }
    }

    // _check optimality conditions
    assert check(G);
}

std::vector<Edge> Kruskal_mst::edges()
{
    return mst;
}

double Kruskal_mst::weight()
{
    return weight;
}

bool Kruskal_mst::check(Edge_weighted_graph& G)
{
    double total = 0.0;
    for (Edge e : edges()) {
        total += e.weight();
    }
    if (std::abs(total - weight()) > FLOATING_POINT_EPSILON) {
        System.err.printf("Weight of edges does not equal weight(): %f vs. %f\n", total, weight());
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
