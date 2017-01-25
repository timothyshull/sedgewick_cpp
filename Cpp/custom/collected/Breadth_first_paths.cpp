#include "Breadth_first_paths.h"

Breadth_first_paths::Breadth_first_paths(Graph& G, int s)
{
    marked = new boolean[G.num_vertices()];
    distance_to = new int[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    bfs(G, s);

    assert check(G, s);
}

Breadth_first_paths::Breadth_first_paths(Graph& G, std::vector<int>& sources)
{
    marked = new boolean[G.num_vertices()];
    distance_to = new int[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        distance_to[v] = INFINITY;
    }
    bfs(G, sources);
}

bool Breadth_first_paths::has_path_to(int v)
{
    return marked[v];
}

int Breadth_first_paths::distance_to(int v)
{
    return distance_to[v];
}

std::vector<int> Breadth_first_paths::path_to(int v)
{
    if (!has_path_to(v)) { return null; }
    Stack <Integer> path = new Stack<Integer>();
    int x;
    for (x = v; distance_to[x] != 0; x = edgeTo[x]) {
        path.push(x);
    }
    path.push(x);
    return path;
}

void Breadth_first_paths::bfs(Graph& G, int s)
{
    Queue <Integer> q = new Queue<Integer>();
    for (int v = 0; v < G.num_vertices(); ++v) {
        distance_to[v] = INFINITY;
    }
    distance_to[s] = 0;
    marked[s] = true;
    q.enqueue(s);

    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distance_to[w] = distance_to[v] + 1;
                marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}

void Breadth_first_paths::bfs(Graph& G, std::vector<int>& sources)
{
    Queue <Integer> q = new Queue<Integer>();
    for (int s : sources) {
        marked[s] = true;
        distance_to[s] = 0;
        q.enqueue(s);
    }
    while (!q.is_empty()) {
        int v = q.dequeue();
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distance_to[w] = distance_to[v] + 1;
                marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}

bool Breadth_first_paths::check(Graph& G, int s)
{
    if (distance_to[s] != 0) {
        Std_out::print_line("distance of source " + s + " to itself = " + distance_to[s]);
        return false;
    }

    // check that for each edge v-w dist[w] <= dist[v] + 1
    // provided v is reachable from s
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (int w : G.adj(v)) {
            if (has_path_to(v) != has_path_to(w)) {
                Std_out::print_line("edge " + v + "-" + w);
                Std_out::print_line("has_path_to(" + v + ") = " + has_path_to(v));
                Std_out::print_line("has_path_to(" + w + ") = " + has_path_to(w));
                return false;
            }
            if (has_path_to(v) && (distance_to[w] > distance_to[v] + 1)) {
                Std_out::print_line("edge " + v + "-" + w);
                Std_out::print_line("_distance_to[" + v + "] = " + distance_to[v]);
                Std_out::print_line("_distance_to[" + w + "] = " + distance_to[w]);
                return false;
            }
        }
    }

    // check that v = edgeTo[w] satisfies _distance_to[w] = _distance_to[v] + 1
    // provided v is reachable from s
    for (int w = 0; w < G.num_vertices(); ++w) {
        if (!has_path_to(w) || w == s) { continue; }
        int v = edgeTo[w];
        if (distance_to[w] != distance_to[v] + 1) {
            Std_out::print_line("shortest path edge " + v + "-" + w);
            Std_out::print_line("_distance_to[" + v + "] = " + distance_to[v]);
            Std_out::print_line("_distance_to[" + w + "] = " + distance_to[w]);
            return false;
        }
    }

    return true;
}
