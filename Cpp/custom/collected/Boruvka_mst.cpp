#include "Boruvka_mst.h"

Boruvka_mst::Boruvka_mst(Edge_weighted_digraph& G)
{
    UF uf = new UF(G.V());

    // repeat at most log V times or until we have V-1 edges
    for (int t = 1; t < G.V() && mst.size() < G.V() - 1; t = t + t) {

        // foreach tree in forest, find closest edge
        // if edge weights are equal, ties are broken in favor of first edge in G.edges()
        Edge[]
        closest = new Edge[G.V()];
        for (Edge e : G.edges()) {
            int v = e.either(), w = e.other(v);
            int i = uf.find(v), j = uf.find(w);
            if (i == j) { continue; }   // same tree
            if (closest[i] == null || less(e, closest[i])) closest[i] = e;
            if (closest[j] == null || less(e, closest[j])) closest[j] = e;
        }

        // add newly discovered edges to MST
        for (int i = 0; i < G.V(); i++) {
            Edge e = closest[i];
            if (e != null) {
                int v = e.either(), w = e.other(v);
                // don't add the same edge twice
                if (!uf.connected(v, w)) {
                    mst.add(e);
                    weight += e.weight();
                    uf.
                    union(v, w);
                }
            }
        }
    }

    // check optimality conditions
    assert check(G);
}

std::vector<Edge> Boruvka_mst::edges()
{
    return mst;
}

double Boruvka_mst::weight()
{
    return weight;
}

bool Boruvka_mst::less(Edge& e, Edge& f)
{
    return e.weight() < f.weight();
}

bool Boruvka_mst::check(Edge_weighted_digraph& g)
{
    // check weight
    double totalWeight = 0.0;
    for (Edge e : edges()) {
        totalWeight += e.weight();
    }
    if (Math.abs(totalWeight - weight()) > FLOATING_POINT_EPSILON) {
        System.err.printf("Weight of edges does not equal weight(): %f vs. %f\n", totalWeight, weight());
        return false;
    }

    // check that it is acyclic
    UF uf = new UF(G.V());
    for (Edge e : edges()) {
        int v = e.either(), w = e.other(v);
        if (uf.connected(v, w)) {
            System.err.println("Not a forest");
            return false;
        }
        uf.
        union(v, w);
    }

    // check that it is a spanning forest
    for (Edge e : G.edges()) {
        int v = e.either(), w = e.other(v);
        if (!uf.connected(v, w)) {
            System.err.println("Not a spanning forest");
            return false;
        }
    }

    // check that it is a minimal spanning forest (cut optimality conditions)
    for (Edge e : edges()) {

        // all edges in MST except e
        uf = new UF(G.V());
        for (Edge f : mst) {
            int x = f.either(), y = f.other(x);
            if (f != e) { uf. }
            union(x, y);
        }

        // check that e is min weight edge in crossing cut
        for (Edge f : G.edges()) {
            int x = f.either(), y = f.other(x);
            if (!uf.connected(x, y)) {
                if (f.weight() < e.weight()) {
                    System.err.println("Edge " + f + " violates cut optimality conditions");
                    return false;
                }
            }
        }

    }

    return true;
}
