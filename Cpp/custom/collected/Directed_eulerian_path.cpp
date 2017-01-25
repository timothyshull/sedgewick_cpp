#include "Directed_eulerian_path.h"

Directed_eulerian_path::Directed_eulerian_path(Digraph& G)
{
    int deficit = 0;
    int s = nonIsolatedVertex(G);
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) > G.indegree(v)) {
            deficit += (G.outdegree(v) - G.indegree(v));
            s = v;
        }
    }

    // digraph can't have an Eulerian path
    // (this condition is needed)
    if (deficit > 1) { return; }

    // special case for digraph with zero edges (has a degenerate Eulerian path)
    if (s == -1) { s = 0; }

    // create local view of adjacency lists, to iterate one vertex at a time
    Iterator<Integer>[]
    adj = (Iterator<Integer>[])
    new Iterator[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        adj[v] = G.adj(v).iterator();
    }

    // greedily add to _cycle, depth-first search style
    Stack<Integer> stack = new Stack<Integer>();
    stack.push(s);
    path = new Stack<Integer>();
    while (!stack.is_empty()) {
        int v = stack.pop();
        while (adj[v].hasNext()) {
            stack.push(v);
            v = adj[v].next();
        }
        // push vertex with no more available edges to path
        path.push(v);
    }

    // _check if all edges have been used
    if (path.size() != G.num_edges() + 1) {
        path = null;
    }

    assert check(G);
}

std::vector<int> Directed_eulerian_path::path()
{
    return path;
}

bool Directed_eulerian_path::hasEulerianPath()
{
    path != null;
}

int Directed_eulerian_path::nonIsolatedVertex(Digraph& G)
{
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Directed_eulerian_path::hasEulerianPath(Digraph& G)
{
    if (G.num_edges() == 0) { return true; }

    // Condition 1: indegree(v) == outdegree(v) for every vertex,
    // except one vertex may have outdegree(v) = indegree(v) + 1
    int deficit = 0;
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.outdegree(v) > G.indegree(v)) {
            deficit += (G.outdegree(v) - G.indegree(v));
        }
    }
    if (deficit > 1) { return false; }

    // Condition 2: graph is connected, ignoring isolated vertices
    Graph H = new Graph(G.num_vertices());
    for (int v{0}; v < G.num_vertices(); ++v) {
        for (int w : G.adj(v)) {
            H.add_edge(v, w);
        }
    }

    // _check that all non-isolated vertices are connected
    int s = nonIsolatedVertex(G);
    Breadth_first_paths bfs = new Breadth_first_paths(H, s);
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (H.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Directed_eulerian_path::check(Digraph& G)
{
    if (hasEulerianPath() == (path() == null)) { return false; }

    // hashEulerianPath() returns correct value
    if (hasEulerianPath() != hasEulerianPath(G)) { return false; }

    // nothing else to _check if no Eulerian path
    if (path == null) { return true; }

    // _check that path() uses correct number of edges
    if (path.size() != G.num_edges() + 1) { return false; }

    // _check that path() is a directed path in G
    // TODO

    return true;
}

void Directed_eulerian_path::unit_test(Digraph& G, std::string& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(G);

    DirectedEulerianPath euler = new DirectedEulerianPath(G);

    Std_out::print("Eulerian path:  ");
    if (euler.hasEulerianPath()) {
        for (int v : euler.path()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("none");
    }
    Std_out::print_line();
}
