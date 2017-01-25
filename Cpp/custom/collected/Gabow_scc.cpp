#include "Gabow_scc.h"

Gabow_scc::Gabow_scc(Digraph& G)
{
    marked = new boolean[G.num_vertices()];
    stack1 = new Stack<Integer>();
    stack2 = new Stack<Integer>();
    id = new int[G.num_vertices()];
    preorder = new int[G.num_vertices()];
    for (int v = 0; v < G.num_vertices(); ++v) {
        id[v] = -1;
    }

    for (int v = 0; v < G.num_vertices(); ++v) {
        if (!marked[v]) { dfs(G, v); }
    }

    // check that id[] gives strong components
    assert check(G);
}

int Gabow_scc::count()
{
    return count;
}

bool Gabow_scc::stronglyCOnnected(int v, int w)
{
    return id[v] == id[w];
}

int Gabow_scc::id(int v)
{
    return id[v];
}

void Gabow_scc::dfs(Digraph& G, int v)
{
    marked[v] = true;
    preorder[v] = ++pre;
    stack1.push(v);
    stack2.push(v);
    for (int w : G.adj(v)) {
        if (!marked[w]) { dfs(G, w); }
        else if (id[w] == -1) {
            while (preorder[stack2.peek()] > preorder[w]) {
                stack2.pop();
            }
        }
    }

    // found strong component containing v
    if (stack2.peek() == v) {
        stack2.pop();
        int w;
        do {
            w = stack1.pop();
            id[w] = count;
        } while (w != v);
        ++count;
    }
}

bool Gabow_scc::check(Digraph& G)
{
    TransitiveClosure tc = new TransitiveClosure(G);
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (int w = 0; w < G.num_vertices(); ++w) {
            if (stronglyConnected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v))) {
                return false;
            }
        }
    }
    return true;
}
