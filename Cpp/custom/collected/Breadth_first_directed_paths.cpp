#include "Breadth_first_directed_paths.h"

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& G, int s)
{
    marked = new boolean[G.num_vertices()];
    distance_to = new int[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        distance_to[v] = INFINITY;
    }
    bfs(G, s);
}

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& G, std::vector<int>& sources)
{
    marked = new boolean[G.num_vertices()];
    distance_to = new int[G.num_vertices()];
    edgeTo = new int[G.num_vertices()];
    for (int v{0}; v < G.num_vertices(); ++v) {
        distance_to[v] = INFINITY;
    }
    bfs(G, sources);
}

bool Breadth_first_directed_paths::has_path_to(int v)
{
    return marked[v];
}

int Breadth_first_directed_paths::distance_to(int v)
{
    return distance_to[v];
}

std::vector<int> Breadth_first_directed_paths::path_to(int v)
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

void Breadth_first_directed_paths::bfs(Digraph& G, int s)
{
    Queue <Integer> q = new Queue<Integer>();
    marked[s] = true;
    distance_to[s] = 0;
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

void Breadth_first_directed_paths::bfs(Digraph& G, std::vector<int>& sources)
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
