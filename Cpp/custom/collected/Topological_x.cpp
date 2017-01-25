#include "Topological_x.h"

Topological_x::Topological_x(Digraph& G)
{
    std::vector<int> indegree = new int[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        indegree[v] = G.indegree(v);
    }

    // initialize
    rank = new int[G.num_vertices()];
    order = new Queue<Integer>();
    int count = 0;

    // initialize queue to contain all vertices with indegree = 0
    Queue<Integer> queue = new Queue<Integer>();
    for (int v = 0; v < G.num_vertices(); ++v)
        if (indegree[v] == 0) queue.enqueue(v);

    for (int j = 0; !queue.is_empty(); ++j) {
        int v = queue.dequeue();
        order.enqueue(v);
        rank[v] = ++count;
        for (int w : G.adj(v)) {
            indegree[w]--;
            if (indegree[w] == 0) queue.enqueue(w);
        }
    }

    // there is a directed cycle in subgraph of vertices with indegree >= 1.
    if (count != G.num_vertices()) {
        order = null;
    }

    assert check(G);
}

Topological_x::Topological_x(Edge_weighted_digraph& G)
{
    std::vector<int> indegree = new int[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        indegree[v] = G.indegree(v);
    }

    // initialize
    rank = new int[G.num_vertices()];
    order = new Queue<Integer>();
    int count = 0;

    // initialize queue to contain all vertices with indegree = 0
    Queue<Integer> queue = new Queue<Integer>();
    for (int v = 0; v < G.num_vertices(); ++v)
        if (indegree[v] == 0) queue.enqueue(v);

    for (int j = 0; !queue.is_empty(); ++j) {
        int v = queue.dequeue();
        order.enqueue(v);
        rank[v] = ++count;
        for (Directed_edge e : G.adj(v)) {
            int w = e.to();
            indegree[w]--;
            if (indegree[w] == 0) queue.enqueue(w);
        }
    }

    // there is a directed cycle in subgraph of vertices with indegree >= 1.
    if (count != G.num_vertices()) {
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
        // check that ranks are a permutation of 0 to _num_vertices-1
        std::deque<bool> found = new boolean[G.num_vertices()];
        for (int i = 0; i < G.num_vertices(); ++i) {
            found[rank(i)] = true;
        }
        for (int i = 0; i < G.num_vertices(); ++i) {
            if (!found[i]) {
                System.err.print_line("No vertex with rank " + i);
                return false;
            }
        }

        // check that ranks provide a valid topological order
        for (int v = 0; v < G.num_vertices(); ++v) {
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
                System.err.print_line("order() and rank() inconsistent");
                return false;
            }
            ++r;
        }
    }

    return true;
}

bool Topological_x::check(Edge_weighted_digraph& G)
{
    if (hasOrder()) {
        // check that ranks are a permutation of 0 to _num_vertices-1
        std::deque<bool> found = new boolean[G.num_vertices()];
        for (int i = 0; i < G.num_vertices(); ++i) {
            found[rank(i)] = true;
        }
        for (int i = 0; i < G.num_vertices(); ++i) {
            if (!found[i]) {
                System.err.print_line("No vertex with rank " + i);
                return false;
            }
        }

        // check that ranks provide a valid topological order
        for (int v = 0; v < G.num_vertices(); ++v) {
            for (Directed_edge e : G.adj(v)) {
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
                System.err.print_line("order() and rank() inconsistent");
                return false;
            }
            ++r;
        }
    }


    return true;
}

void Topological_x::validateVertex(int v)
{
    int num_vertices = rank.length;
    if (v < 0 || v >= V)
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
}
