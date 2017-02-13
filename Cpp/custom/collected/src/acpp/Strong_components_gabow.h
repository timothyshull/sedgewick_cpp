#ifndef STRONG_COMPONENTS_GABOW_H
#define STRONG_COMPONENTS_GABOW_H

#include "STACK.cc"

template<typename Graph> class SC {
    const Graph& G;
    STACK<int> S;
    int cnt, scnt;
    vector<int> pre, low, id;

    void scR(int w)
    {
        int v;
        pre[w] = cnt++;
        S.push(w);
        path.push(w);
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[t] == -1) { scR(t); }
            else if (id[t] == -1) {
                while (pre[path.top()] > pre[t]) { path.pop(); }
            }
        }
        if (path.top() == w) { path.pop(); } else { return; }
        do { id[v = S.pop()] = scnt; } while (v != w);
        scnt++;
    }

public:
    SC(const Graph& G) : G(G), cnt(0), scnt(0),
                         pre(G.V(), -1), low(G.V()), id(G.V())
    {
        for (int v = 0; v < G.V(); v++) {
            if (pre[v] == -1) { scR(v); }
        }
    }

    int count() const { return scnt; }

    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
};





#endif // STRONG_COMPONENTS_GABOW_H
