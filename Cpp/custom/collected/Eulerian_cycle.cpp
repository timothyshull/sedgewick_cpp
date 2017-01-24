#include "Eulerian_cycle.h"

Edge::Edge(int v, int w) : v{v}, w{w}, isUsed{false} {}

int Edge::other(int vertex)
{
    if (vertex == v) { return w; }
    else if (vertex == w) { return v; }
    else { throw new IllegalArgumentException("Illegal endpoint"); }
}

Eulerian_cycle::Eulerian_cycle(Graph& G)
{
    if (G.num_edges() == 0) { return; }

    // necessary condition: all vertices have even degree
    // (this test is needed or it might find an Eulerian path instead of cycle)
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (G.degree(v) % 2 != 0) {
            return;
        }
    }

    // create local view of adjacency lists, to iterate one vertex at a time
    // the helper Edge data type is used to avoid exploring both copies of an edge v-w
    Queue<Edge>[]
    adj = (Queue<Edge>[])
    new Queue[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        adj[v] = new Queue<Edge>();
    }

    for (int v = 0; v < G.num_vertices(); ++v) {
        int selfLoops = 0;
        for (int w : G.adj(v)) {
            // careful with self loops
            if (v == w) {
                if (selfLoops % 2 == 0) {
                    Edge e = new Edge(v, w);
                    adj[v].enqueue(e);
                    adj[w].enqueue(e);
                }
                selfLoops++;
            } else if (v < w) {
                Edge e = new Edge(v, w);
                adj[v].enqueue(e);
                adj[w].enqueue(e);
            }
        }
    }

    // initialize stack with any non-isolated vertex
    int s = nonIsolatedVertex(G);
    Stack<Integer> stack = new Stack<Integer>();
    stack.push(s);

    // greedily search through edges in iterative DFS style
    cycle = new Stack<Integer>();
    while (!stack.is_empty()) {
        int v = stack.pop();
        while (!adj[v].is_empty()) {
            Edge edge = adj[v].dequeue();
            if (edge.isUsed) { continue; }
            edge.isUsed = true;
            stack.push(v);
            v = edge.other(v);
        }
        // push vertex with no more leaving edges to cycle
        cycle.push(v);
    }

    // check if all edges are used
    if (cycle.size() != G.num_edges() + 1) {
        cycle = null;
    }

    assert certifySolution(G);
}

std::vector<int> Eulerian_cycle::cycle()
{
    return cycle;
}

bool Eulerian_cycle::hasEulerianCycle()
{
    return cycle != null;
}

int Eulerian_cycle::nonIsolatedVertex(Graph& G)
{
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (G.degree(v) > 0) {
            return v;
        }
    }
    return -1;
}

bool Eulerian_cycle::hasEulerianCycle(Graph& G)
{
    if (G.num_edges() == 0) { return false; }

    // Condition 1: degree(v) is even for every vertex
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (G.degree(v) % 2 != 0) {
            return false;
        }
    }

    // Condition 2: graph is connected, ignoring isolated vertices
    int s = nonIsolatedVertex(G);
    Breadth_first_paths bfs = new Breadth_first_paths(G, s);
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (G.degree(v) > 0 && !bfs.has_path_to(v)) {
            return false;
        }
    }

    return true;
}

bool Eulerian_cycle::certifySolution(Graph& G)
{
    if (hasEulerianCycle() == (cycle() == null)) { return false; }

    // hashEulerianCycle() returns correct value
    if (hasEulerianCycle() != hasEulerianCycle(G)) { return false; }

    // nothing else to check if no Eulerian cycle
    if (cycle == null) { return true; }

    // check that cycle() uses correct number of edges
    if (cycle.size() != G.num_edges() + 1) { return false; }

    // check that cycle() is a cycle of G
    // TODO

    // check that first and last vertices in cycle() are the same
    int first = -1, last = -1;
    for (int v : cycle()) {
        if (first == -1) { first = v; }
        last = v;
    }
    if (first != last) { return false; }

    return true;
}

void Eulerian_cycle::unit_test(Graph& G, std::string& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(G);

    EulerianCycle euler = new EulerianCycle(G);

    Std_out::print("Eulerian cycle: ");
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
