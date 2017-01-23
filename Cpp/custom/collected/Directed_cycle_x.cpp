#include "Directed_cycle_x.h"
#include "Digraph.h"

Directed_cycle_x::Directed_cycle_x(Digraph& G)
{
    int[] indegree = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        indegree[v] = G.indegree(v);
    }

    // initialize queue to contain all vertices with indegree = 0
    Queue<Integer> queue = new Queue<Integer>();
    for (int v = 0; v < G.V(); v++)
        if (indegree[v] == 0) queue.enqueue(v);

    for (int j = 0; !queue.isEmpty(); j++) {
        int v = queue.dequeue();
        for (int w : G.adj(v)) {
            indegree[w]--;
            if (indegree[w] == 0) queue.enqueue(w);
        }
    }

    // there is a directed cycle in subgraph of vertices with indegree >= 1.
    int[] edgeTo = new int[G.V()];
    int root = -1;  // any vertex with indegree >= -1
    for (int v = 0; v < G.V(); v++) {
        if (indegree[v] == 0) continue;
        else root = v;
        for (int w : G.adj(v)) {
            if (indegree[w] > 0) {
                edgeTo[w] = v;
            }
        }
    }

    if (root != -1) {

        // find any vertex on cycle
        boolean[] visited = new boolean[G.V()];
        while (!visited[root]) {
            visited[root] = true;
            root = edgeTo[root];
        }

        // extract cycle
        cycle = new Stack<Integer>();
        int v = root;
        do {
            cycle.push(v);
            v = edgeTo[v];
        } while (v != root);
        cycle.push(root);
    }

    assert check();
}

std::vector<int> Directed_cycle_x::cycle()
{
    return cycle;
}

bool Directed_cycle_x::hasCycle()
{
    return cycle != null;
}

bool Directed_cycle_x::check()
{
    if (hasCycle()) {
        // verify cycle
        int first = -1, last = -1;
        for (int v : cycle()) {
            if (first == -1) first = v;
            last = v;
        }
        if (first != last) {
            System.err.printf("cycle begins with %d and ends with %d\n", first, last);
            return false;
        }
    }


    return true;
}
