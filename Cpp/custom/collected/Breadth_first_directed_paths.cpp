#include "Breadth_first_directed_paths.h"

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& G, int s)
{
    marked = new boolean[G.V()];
    distTo = new int[G.V()];
    edgeTo = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        distTo[v] = INFINITY;
    }
    bfs(G, s);
}

Breadth_first_directed_paths::Breadth_first_directed_paths(Digraph& G, std::vector<int>& sources)
{
    marked = new boolean[G.V()];
    distTo = new int[G.V()];
    edgeTo = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        distTo[v] = INFINITY;
    }
    bfs(G, sources);
}

bool Breadth_first_directed_paths::hasPathTo(int v)
{
    return marked[v];
}

int Breadth_first_directed_paths::distTo(int v)
{
    return distTo[v];
}

std::vector<int> Breadth_first_directed_paths::pathTo(int v)
{
    if (!hasPathTo(v)) { return null; }
    Stack <Integer> path = new Stack<Integer>();
    int x;
    for (x = v; distTo[x] != 0; x = edgeTo[x]) {
        path.push(x);
    }
    path.push(x);
    return path;
}

void Breadth_first_directed_paths::bfs(Digraph& G, int s)
{
    Queue <Integer> q = new Queue<Integer>();
    marked[s] = true;
    distTo[s] = 0;
    q.enqueue(s);
    while (!q.isEmpty()) {
        int v = q.dequeue();
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distTo[w] = distTo[v] + 1;
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
        distTo[s] = 0;
        q.enqueue(s);
    }
    while (!q.isEmpty()) {
        int v = q.dequeue();
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distTo[w] = distTo[v] + 1;
                marked[w] = true;
                q.enqueue(w);
            }
        }
    }
}
