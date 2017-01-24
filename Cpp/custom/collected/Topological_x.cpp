#include "Topological_x.h"

Topological_x::Topological_x(Digraph& G)
{
    int[] indegree = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        indegree[v] = G.indegree(v);
    }

    // initialize
    rank = new int[G.V()];
    order = new Queue<Integer>();
    int count = 0;

    // initialize queue to contain all vertices with indegree = 0
    Queue<Integer> queue = new Queue<Integer>();
    for (int v = 0; v < G.V(); v++)
        if (indegree[v] == 0) queue.enqueue(v);

    for (int j = 0; !queue.isEmpty(); j++) {
        int v = queue.dequeue();
        order.enqueue(v);
        rank[v] = count++;
        for (int w : G.adj(v)) {
            indegree[w]--;
            if (indegree[w] == 0) queue.enqueue(w);
        }
    }

    // there is a directed cycle in subgraph of vertices with indegree >= 1.
    if (count != G.V()) {
        order = null;
    }

    assert check(G);
}

Topological_x::Topological_x(Edge_weighted_digraph& G)
{
    int[] indegree = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        indegree[v] = G.indegree(v);
    }

    // initialize
    rank = new int[G.V()];
    order = new Queue<Integer>();
    int count = 0;

    // initialize queue to contain all vertices with indegree = 0
    Queue<Integer> queue = new Queue<Integer>();
    for (int v = 0; v < G.V(); v++)
        if (indegree[v] == 0) queue.enqueue(v);

    for (int j = 0; !queue.isEmpty(); j++) {
        int v = queue.dequeue();
        order.enqueue(v);
        rank[v] = count++;
        for (DirectedEdge e : G.adj(v)) {
            int w = e.to();
            indegree[w]--;
            if (indegree[w] == 0) queue.enqueue(w);
        }
    }

    // there is a directed cycle in subgraph of vertices with indegree >= 1.
    if (count != G.V()) {
        order = null;
    }

    assert check(G);
}

std::vector<int> Topological_x::order()
{
    return order;
}

bool Topological_x::has_order()
{
    return order != null;
}

int Topological_x::rank(int v)
{
    validateVertex(v);
    if (hasOrder()) return rank[v];
    else return -1;
}

bool Topological_x::check(Digraph& G)
{
    if (hasOrder()) {
        // check that ranks are a permutation of 0 to V-1
        boolean[] found = new boolean[G.V()];
        for (int i = 0; i < G.V(); i++) {
            found[rank(i)] = true;
        }
        for (int i = 0; i < G.V(); i++) {
            if (!found[i]) {
                System.err.println("No vertex with rank " + i);
                return false;
            }
        }

        // check that ranks provide a valid topological order
        for (int v = 0; v < G.V(); v++) {
            for (int w : G.adj(v)) {
                if (rank(v) > rank(w)) {
                    System.err.printf("%d-%d: rank(%d) = %d, rank(%d) = %d\n",
                                      v, w, v, rank(v), w, rank(w));
                    return false;
                }
            }
        }

        // check that order() is consistent with rank()
        int r = 0;
        for (int v : order()) {
            if (rank(v) != r) {
                System.err.println("order() and rank() inconsistent");
                return false;
            }
            r++;
        }
    }

    return true;
}

bool Topological_x::check(Edge_weighted_digraph& G)
{
    if (hasOrder()) {
        // check that ranks are a permutation of 0 to V-1
        boolean[] found = new boolean[G.V()];
        for (int i = 0; i < G.V(); i++) {
            found[rank(i)] = true;
        }
        for (int i = 0; i < G.V(); i++) {
            if (!found[i]) {
                System.err.println("No vertex with rank " + i);
                return false;
            }
        }

        // check that ranks provide a valid topological order
        for (int v = 0; v < G.V(); v++) {
            for (DirectedEdge e : G.adj(v)) {
                int w = e.to();
                if (rank(v) > rank(w)) {
                    System.err.printf("%d-%d: rank(%d) = %d, rank(%d) = %d\n",
                                      v, w, v, rank(v), w, rank(w));
                    return false;
                }
            }
        }

        // check that order() is consistent with rank()
        int r = 0;
        for (int v : order()) {
            if (rank(v) != r) {
                System.err.println("order() and rank() inconsistent");
                return false;
            }
            r++;
        }
    }


    return true;
}

void Topological_x::validateVertex(int v)
{
    int V = rank.length;
    if (v < 0 || v >= V)
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
}
