#ifndef COLLECTED_MINCOST_NETWORK_SIMPLEX_H
#define COLLECTED_MINCOST_NETWORK_SIMPLEX_H

template<class Graph, class Edge> class MINCOST {
    const Graph& G;
    int s, t;
    int valid;
    vector<Edge*> st;
    vector<int> mark, phi;

    void dfsR(Edge);

    int ST(int);

    int phiR(int v)
    {
        if (mark[v] == valid) { return phi[v]; }
        phi[v] = phiR(ST(v)) - st[v]->costRto(v);
        mark[v] = valid;
        return phi[v];
    }


    int lca(int v, int w)
    {
        mark[v] = ++valid;
        mark[w] = valid;
        while (v != w) {
            if (v != t) { v = ST(v); }
            if (v != t && mark[v] == valid) { return v; }
            mark[v] = valid;
            if (w != t) { w = ST(w); }
            if (w != t && mark[w] == valid) { return w; }
            mark[w] = valid;
        }
        return v;
    }

    Edge* augment(Edge* x)
    {
        int v = x->v(), w = x->w();
        int r = lca(v, w);
        int d = x->capRto(w);
        for (int u = w; u != r; u = ST(u)) {
            if (st[u]->capRto(ST(u)) < d) {
                d = st[u]->capRto(ST(u));
            }
        }
        for (int u = v; u != r; u = ST(u)) {
            if (st[u]->capRto(u) < d) {
                d = st[u]->capRto(u);
            }
        }
        x->addflowRto(w, d);
        Edge* e = x;
        for (int u = w; u != r; u = ST(u)) {
            st[u]->addflowRto(ST(u), d);
            if (st[u]->capRto(ST(u)) == 0) { e = st[u]; }
        }
        for (int u = v; u != r; u = ST(u)) {
            st[u]->addflowRto(u, d);
            if (st[u]->capRto(u) == 0) { e = st[u]; }
        }
        return e;
    }


    bool onpath(int a, int b, int c)
    {
        for (int i = a; i != c; i = ST(i)) {
            if (i == b) { return true; }
        }
        return false;
    }

    void reverse(int u, int x)
    {
        Edge* e = st[u];
        for (int i = ST(u); i != x; i = ST(i)) {
            Edge* y = st[i];
            st[i] = e;
            e = y;
        }
    }

    void update(Edge* w, Edge* y)
    {
        int u = y->w(), v = y->v(), x = w->w();
        if (st[x] != w) { x = w->v(); }
        int r = lca(u, v);
        if (onpath(u, x, r)) {
            reverse(u, x);
            st[u] = y;
            return;
        }
        if (onpath(v, x, r)) {
            reverse(v, x);
            st[v] = y;
            return;
        }
    }



    int costR(Edge* e, int v)
    {
        int R = e->cost() + phi[e->w()] - phi[e->v()];
        return e->from(v) ? R : -R;
    }

    Edge* besteligible()
    {
        Edge* x = 0;
        for (int v = 0, min = C * G.V(); v < G.V(); v++) {
            typename Graph::adjIterator A(G, v);
            for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
                if (e->capRto(e->other(v)) > 0) {
                    if (e->capRto(v) == 0) {
                        if (costR(e, v) < min) {
                            x = e;
                            min = costR(e, v);
                        }
                    }
                }
            }
        }
        return x;
    }


public:
    MINCOST(Graph& G, int s, int t) : G(G), s(s), t(t),
                                      st(G.V()), mark(G.V(), -1), phi(G.V())
    {
        Edge* z = new EDGE(s, t, M * G.V(), C * G.V());
        G.insert(z);
        z->addflowto(t, z->cap());
        dfsR(z);
        for (valid = 1;; valid++) {
            phi[t] = z->costRto(s);
            mark[t] = valid;
            for (int v = 0; v < G.V(); v++) {
                if (v != t) { phi[v] = phiR(v); }
            }
            Edge* x = besteligible();
            if (costR(x, x->v()) == 0) { break; }
            update(augment(x), x);
        }
        G.remove(z);
        delete z;
    }
};

#endif // COLLECTED_MINCOST_NETWORK_SIMPLEX_H
