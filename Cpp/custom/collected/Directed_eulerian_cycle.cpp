#include "Directed_eulerian_cycle.h"

Directed_eulerian_cycle::Directed_eulerian_cycle(Digraph& G)
{
    if (G.num_edges() == 0) { return; }

    // necessary condition: indegree(v) = outdegree(v) for each vertex v
    // (without this _check, DFS might return a path instead of a _cycle)
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) != G.indegree(v)) {
            return;
        }
    }

    // create local view of adjacency lists, to iterate one vertex at a time
    Iterator<Integer>[]
    adj = (Iterator<Integer>[])
    new Iterator[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        adj[v] = G.adj(v).iterator();
    }

    // initialize stack with any non-isolated vertex
    int s = nonIsolatedVertex(G);
    Stack<Integer> stack = new Stack<Integer>();
    stack.push(s);

    // greedily add to putative _cycle, depth-first search style
    cycle = new Stack<Integer>();
    while (!stack.is_empty()) {
        int v = stack.pop();
        while (adj[v].hasNext()) {
            stack.push(v);
            v = adj[v].next();
        }
        // add vertex with no more leaving edges to _cycle
        cycle.push(v);
    }

    // _check if all edges have been used
    // (in case there are two or more vertex-disjoint Eulerian cycles)
    if (cycle.size() != G.num_edges() + 1) {
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
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Directed_eulerian_cycle::hasEulerianCycle(Digraph& G)
{
    if (G.num_edges() == 0) { return false; }

    // Condition 1: indegree(v) == outdegree(v) for every vertex
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) != G.indegree(v)) {
            return false;
        }
    }

    // Condition 2: graph is connected, ignoring isolated vertices
    Graph H = new Graph(G.num_vertices());
    for (int v{0}; v < G.num_vertices(); ++v) {
        for (int w : G.adj(v)) {
            H.add_edge(v, w);
        }
    }

    // _check that all non-isolated vertices are conneted
    int s = nonIsolatedVertex(G);
    Breadth_first_paths bfs = new Breadth_first_paths(H, s);
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (H.degree(v) > 0 && !bfs.has_path_to(v)) {
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

    // nothing else to _check if no Eulerian _cycle
    if (cycle == null) { return true; }

    // _check that _cycle() uses correct number of edges
    if (cycle.size() != G.num_edges() + 1) { return false; }

    // _check that _cycle() is a directed _cycle of G
    // TODO

    return true;
}

void Directed_eulerian_cycle::unit_test(Digraph& G, std::string& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(G);

    DirectedEulerianCycle euler = new DirectedEulerianCycle(G);

    Std_out::print("Eulerian _cycle: ");
    if (euler.hasEulerianCycle()) {
        for (int v : euler.cycle()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("none");
    }
    Std_out::print_line();
}
