#include "Breadth_first_paths.h"

Breadth_first_paths::Breadth_first_paths(Graph& G, int s)
{
    marked = new boolean[G.V()];
    distTo = new int[G.V()];
    edgeTo = new int[G.V()];
    bfs(G, s);

    assert check(G, s);
}

Breadth_first_paths::Breadth_first_paths(Graph& G, std::vector<int>& sources)
{
    marked = new boolean[G.V()];
    distTo = new int[G.V()];
    edgeTo = new int[G.V()];
    for (int v = 0; v < G.V(); v++) {
        distTo[v] = INFINITY;
    }
    bfs(G, sources);
}

bool Breadth_first_paths::hasPathTo(int v)
{
    return marked[v];
}

int Breadth_first_paths::distTo(int v)
{
    return distTo[v];
}

std::vector<int> Breadth_first_paths::pathTo(int v)
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

void Breadth_first_paths::bfs(Graph& G, int s)
{
    Queue <Integer> q = new Queue<Integer>();
    for (int v = 0; v < G.V(); v++) {
        distTo[v] = INFINITY;
    }
    distTo[s] = 0;
    marked[s] = true;
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

void Breadth_first_paths::bfs(Graph& G, std::vector<int>& sources)
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

bool Breadth_first_paths::check(Graph& G, int s)
{
    if (distTo[s] != 0) {
        StdOut.println("distance of source " + s + " to itself = " + distTo[s]);
        return false;
    }

    // check that for each edge v-w dist[w] <= dist[v] + 1
    // provided v is reachable from s
    for (int v = 0; v < G.V(); v++) {
        for (int w : G.adj(v)) {
            if (hasPathTo(v) != hasPathTo(w)) {
                StdOut.println("edge " + v + "-" + w);
                StdOut.println("hasPathTo(" + v + ") = " + hasPathTo(v));
                StdOut.println("hasPathTo(" + w + ") = " + hasPathTo(w));
                return false;
            }
            if (hasPathTo(v) && (distTo[w] > distTo[v] + 1)) {
                StdOut.println("edge " + v + "-" + w);
                StdOut.println("distTo[" + v + "] = " + distTo[v]);
                StdOut.println("distTo[" + w + "] = " + distTo[w]);
                return false;
            }
        }
    }

    // check that v = edgeTo[w] satisfies distTo[w] = distTo[v] + 1
    // provided v is reachable from s
    for (int w = 0; w < G.V(); w++) {
        if (!hasPathTo(w) || w == s) { continue; }
        int v = edgeTo[w];
        if (distTo[w] != distTo[v] + 1) {
            StdOut.println("shortest path edge " + v + "-" + w);
            StdOut.println("distTo[" + v + "] = " + distTo[v]);
            StdOut.println("distTo[" + w + "] = " + distTo[w]);
            return false;
        }
    }

    return true;
}
