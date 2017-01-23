#include "Directed_eulerian_cycle.h"

Directed_eulerian_cycle::Directed_eulerian_cycle(Digraph& G)
{
    if (G.E() == 0) { return; }

    // necessary condition: indegree(v) = outdegree(v) for each vertex v
    // (without this check, DFS might return a path instead of a cycle)
    for (int v = 0; v < G.V(); v++) {
        if (G.outdegree(v) != G.indegree(v)) {
            return;
        }
    }

    // create local view of adjacency lists, to iterate one vertex at a time
    Iterator<Integer>[]
    adj = (Iterator<Integer>[])
    new Iterator[G.V()];
    for (int v = 0; v < G.V(); v++) {
        adj[v] = G.adj(v).iterator();
    }

    // initialize stack with any non-isolated vertex
    int s = nonIsolatedVertex(G);
    Stack<Integer> stack = new Stack<Integer>();
    stack.push(s);

    // greedily add to putative cycle, depth-first search style
    cycle = new Stack<Integer>();
    while (!stack.isEmpty()) {
        int v = stack.pop();
        while (adj[v].hasNext()) {
            stack.push(v);
            v = adj[v].next();
        }
        // add vertex with no more leaving edges to cycle
        cycle.push(v);
    }

    // check if all edges have been used
    // (in case there are two or more vertex-disjoint Eulerian cycles)
    if (cycle.size() != G.E() + 1) {
        cycle = null;
    }

    assert certifySolution(G);
}

std::vector<int> Directed_eulerian_cycle::cycle()
{
    return cycle;
}

bool Directed_eulerian_cycle::hasEulerianCycle()
{
    return cycle != null;
}

int Directed_eulerian_cycle::nonIsolatedVertex(Digraph& G)
{
    for (int v = 0; v < G.V(); v++) {
        if (G.outdegree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Directed_eulerian_cycle::hasEulerianCycle(Digraph& G)
{
    if (G.E() == 0) { return false; }

    // Condition 1: indegree(v) == outdegree(v) for every vertex
    for (int v = 0; v < G.V(); v++) {
        if (G.outdegree(v) != G.indegree(v)) {
            return false;
        }
    }

    // Condition 2: graph is connected, ignoring isolated vertices
    Graph H = new Graph(G.V());
    for (int v = 0; v < G.V(); v++) {
        for (int w : G.adj(v)) {
            H.addEdge(v, w);
        }
    }

    // check that all non-isolated vertices are conneted
    int s = nonIsolatedVertex(G);
    BreadthFirstPaths bfs = new BreadthFirstPaths(H, s);
    for (int v = 0; v < G.V(); v++) {
        if (H.degree(v) > 0 && !bfs.hasPathTo(v)) {
            return false;
        }
    }

    return true;
}

bool Directed_eulerian_cycle::certifySolution(Digraph& G)
{
    if (hasEulerianCycle() == (cycle() == null)) { return false; }

    // hashEulerianCycle() returns correct value
    if (hasEulerianCycle() != hasEulerianCycle(G)) { return false; }

    // nothing else to check if no Eulerian cycle
    if (cycle == null) { return true; }

    // check that cycle() uses correct number of edges
    if (cycle.size() != G.E() + 1) { return false; }

    // check that cycle() is a directed cycle of G
    // TODO

    return true;
}

void Directed_eulerian_cycle::unitTest(Digraph& G, std::string& description)
{
    StdOut.println(description);
    StdOut.println("-------------------------------------");
    StdOut.print(G);

    DirectedEulerianCycle euler = new DirectedEulerianCycle(G);

    StdOut.print("Eulerian cycle: ");
    if (euler.hasEulerianCycle()) {
        for (int v : euler.cycle()) {
            StdOut.print(v + " ");
        }
        StdOut.println();
    } else {
        StdOut.println("none");
    }
    StdOut.println();
}
