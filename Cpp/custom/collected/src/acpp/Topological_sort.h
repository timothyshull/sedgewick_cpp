#ifndef COLLECTED_TOPOLOGICAL_SORT_H
#define COLLECTED_TOPOLOGICAL_SORT_H

template<class Dag> class dagTS {
    const Dag& D;
    int cnt, tcnt;
    vector<int> pre, post, postI;

    void tsR(int v)
    {
        pre[v] = cnt++;
        for (int w = 0; w < D.V(); w++) {
            if (D.edge(w, v)) {
                if (pre[w] == -1) { tsR(w); }
            }
        }
        post[v] = tcnt;
        postI[tcnt++] = v;
    }

public:
    dagTS(const Dag& D) : D(D), tcnt(0), cnt(0),
                          pre(D.V(), -1), post(D.V(), -1), postI(D.V(), -1)
    {
        for (int v = 0; v < D.V(); v++) {
            if (pre[v] == -1) { tsR(v); }
        }
    }

    int operator[](int v) const { return postI[v]; }

    int relabel(int v) const { return post[v]; }
};



#endif // COLLECTED_TOPOLOGICAL_SORT_H
