#ifndef MINCOST_RESIDUAL_NETWORKS_H
#define MINCOST_RESIDUAL_NETWORKS_H

template<typename Graph, typename Edge> class MINCOST {
    const Graph& G;
    int s, t;
    vector<int> wt;
    vector<Edge*> st;

    int ST(int v) const;

    void augment(int, int);

    int negcyc(int);

    int negcyc();

public:
    MINCOST(const Graph& G, int s, int t) : G(G),
                                            s(s), t(t), st(G.V()), wt(G.V())
    {
        MAXFLOW<Graph, Edge>(G, s, t);
        for (int x = negcyc(); x != -1; x = negcyc()) { augment(x, x); }
    }
};



#endif // MINCOST_RESIDUAL_NETWORKS_H
