#ifndef COLLECTED_TRANSITIVE_CLOSURE_DFS_H
#define COLLECTED_TRANSITIVE_CLOSURE_DFS_H

template<class Graph> class tc {
    Graph T;
    const Graph& G;

    void tcR(int v, int w)
    {
        T.insert(Edge(v, w));
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!T.edge(v, t)) { tcR(v, t); }
        }
    }

public:
    tc(const Graph& G) : G(G), T(G.V(), true) { for (int v = 0; v < G.V(); v++) { tcR(v, v); }}

    bool reachable(int v, int w) { return T.edge(v, w); }
};



#endif // COLLECTED_TRANSITIVE_CLOSURE_DFS_H
