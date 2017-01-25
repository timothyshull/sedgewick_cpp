#include "Eulerian_path.h"

Edge::Edge(int v, int w) : v{v}, w{w}, isUsed{false} {}

int Edge::other(int vertex)
{
    if (vertex == v) { return w; }
    else if (vertex == w) { return v; }
    else { throw utility::Illegal_argument_exception("Illegal endpoint"); }
}

Eulerian_path::Eulerian_path(Graph& G)
{
    int oddDegreeVertices = 0;
    int s = nonIsolatedVertex(G);
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (G.degree(v) % 2 != 0) {
            ++oddDegreeVertices;
            s = v;
        }
    }

    // graph can't have an Eulerian path
    // (this condition is needed for correctness)
    if (oddDegreeVertices > 2) return;

    // special case for graph with zero edges (has a degenerate Eulerian path)
    if (s == -1) s = 0;

    // create local view of adjacency lists, to iterate one vertex at a time
    // the helper Edge data type is used to avoid exploring both copies of an edge v-w
    Queue<Edge>[] adj = (Queue<Edge>[]) new Queue[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v)
        adj[v] = new Queue<Edge>();

    for (int v{0}; v < G.num_vertices(); ++v) {
        int selfLoops = 0;
        for (int w : G.adj(v)) {
            // careful with self loops
            if (v == w) {
                if (selfLoops % 2 == 0) {
                    Edge e = new Edge(v, w);
                    adj[v].enqueue(e);
                    adj[w].enqueue(e);
                }
                ++selfLoops;
            } else if (v < w) {
                Edge e = new Edge(v, w);
                adj[v].enqueue(e);
                adj[w].enqueue(e);
            }
        }
    }

    // initialize stack with any non-isolated vertex
    Stack<Integer> stack = new Stack<Integer>();
    stack.push(s);

    // greedily search through edges in iterative DFS style
    path = new Stack<Integer>();
    while (!stack.is_empty()) {
        int v = stack.pop();
        while (!adj[v].is_empty()) {
            Edge edge = adj[v].dequeue();
            if (edge.isUsed) continue;
            edge.isUsed = true;
            stack.push(v);
            v = edge.other(v);
        }
        // push vertex with no more leaving edges to path
        path.push(v);
    }

    // _check if all edges are used
    if (path.size() != G.num_edges() + 1)
        path = null;

    assert certifySolution(G);
}

std::vector<int> Eulerian_path::path()
{
    return path;
}

bool Eulerian_path::hasEulerianPath()
{
    return path != null;
}

int Eulerian_path::nonIsolatedVertex(Graph& G)
{
    for (int v{0}; v < G.num_vertices(); ++v)
        if (G.degree(v) > 0)
            return v;
    return -1;
}

bool Eulerian_path::hasEulerianPath(Graph& G)
{
    if (G.num_edges() == 0) return true;

    // Condition 1: degree(v) is even except for possibly two
    int oddDegreeVertices = 0;
    for (int v{0}; v < G.num_vertices(); ++v)
        if (G.degree(v) % 2 != 0)
            ++oddDegreeVertices;
    if (oddDegreeVertices > 2) return false;

    // Condition 2: graph is connected, ignoring isolated vertices
    int s = nonIsolatedVertex(G);
    Breadth_first_paths bfs = new Breadth_first_paths(G, s);
    for (int v{0}; v < G.num_vertices(); ++v)
        if (G.degree(v) > 0 && !bfs.has_path_to(v))
            return false;

    return true;
}

bool Eulerian_path::ceertifySolution(Graph& G)
{
    if (hasEulerianPath() == (path() == null)) return false;

    // hashEulerianPath() returns correct value
    if (hasEulerianPath() != hasEulerianPath(G)) return false;

    // nothing else to _check if no Eulerian path
    if (path == null) return true;

    // _check that path() uses correct number of edges
    if (path.size() != G.num_edges() + 1) return false;

    // _check that path() is a path in G
    // TODO

    return true;
}

void Eulerian_path::unit_test(Graph& G, std::string& description)
{
    Std_out::print_line(description);
    Std_out::print_line("-------------------------------------");
    Std_out::print(G);

    EulerianPath euler = new EulerianPath(G);

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
