#include "GRAPHbasic.cc"
#include "GRAPHio.cc"
#include "LPTdag.cc"

typedef WeightedEdge EDGE;

typedef DenseGRAPH <EDGE> GRAPH;

int main(int argc, char* argv[])
{
    int i, s, t, N = atoi(argv[1]);
    double duration[N];
    GRAPH G(N, true);
    for (int i = 0; i < N; i++) {
        cin >> duration[i];
    }
    while (cin >> s >> t) {
        G.insert(new EDGE(s, t, duration[s]));
    }
    LPTdag <GRAPH, EDGE> lpt(G);
    for (i = 0; i < N; i++) {
        cout << i << " " << lpt.dist(i) << "\n";
    }
}

