#ifndef COLLECTED_SHORTEST_PATHS_BELLMAN_FORD_H
#define COLLECTED_SHORTEST_PATHS_BELLMAN_FORD_H

template<class Graph, class Edge> class SPT {
    const Graph& G;
    vector<double> wt;
    vector<Edge*> spt;
public:
    SPT(Graph &G, int s) : G(G),
                           spt(G.V()), wt(G.V(), G.V())
    { QUEUE<int> Q; int N = 0;
        wt[s] = 0.0;
        Q.put(s); Q.put(G.V());
        while (!Q.empty())
        { int v;
            while ((v = Q.get()) == G.V())
            { if (N++ > G.V()) return; Q.put(G.V()); }
            typename Graph::adjIterator A(G, v);
            for (Edge* e = A.beg(); !A.end(); e = A.nxt())
            { int w = e->w();
                double P = wt[v] + e->wt();
                if (P < wt[w])
                { wt[w] = P; Q.put(w); spt[w] = e; }
            }
        }
    }

    Edge* pathR(int v) const { return spt[v]; }

    double dist(int v) const { return wt[v]; }
};




#endif // COLLECTED_SHORTEST_PATHS_BELLMAN_FORD_H
