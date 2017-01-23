#ifndef KOSARAJU_SHARIR_SCC_H
#define KOSARAJU_SHARIR_SCC_H

#include <deque>
#include <vector>
#include "Digraph.h"

class Kosaraju_sharir_scc {
public:
    Kosaraju_sharir_scc(Digraph& G);

    int count();
    bool stronglyConnected(int v, int w);
    int id(int v);
private:
    std::deque<bool> marked;
    std::vector<int> id;
    int count;

    void dfs(Digraph& G, int v);

    bool check(Digraph& G);
};

#endif // KOSARAJU_SHARIR_SCC_H
