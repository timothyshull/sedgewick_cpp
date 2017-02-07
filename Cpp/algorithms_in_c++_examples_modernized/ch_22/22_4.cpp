template<class Graph, class Edge>
bool MAXFLOW<Graph, Edge>::pfs()
{
    PQi<int> pQ(G.V(), wt);
    for (int v = 0; v < G.V(); ++v) {
        wt[v] = 0;
        st[v] = 0;
        pQ.insert(v);
    }
    wt[s] = -M;
    pQ.lower(s);
    while (!pQ.empty()) {
        int v = pQ.getmin();
        wt[v] = -M;
        if (v == t || (v != s && st[v] == 0)) { break; }
        typename Graph::adjIterator A(G, v);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            int w = e->other(v);
            int cap = e->capRto(w);
            int P = cap < -wt[v] ? cap : -wt[v];
            if (cap > 0 && -P < wt[w]) {
                wt[w] = -P;
                pQ.lower(w);
                st[w] = e;
            }
        }
    }
    return st[t] != 0;
}

