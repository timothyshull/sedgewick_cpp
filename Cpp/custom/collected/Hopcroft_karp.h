#ifndef HOPCROFT_KARP_H
#define HOPCROFT_KARP_H

#include <vector>
#include <deque>
#include "Graph.h"

class Hopcroft_karp {
public:
    Hopcroft_karp(Graph& G);

    int mate(int v);

    bool isMatched(int v);

    int size();

    bool isPerfect();

    bool inMinVertexCover(int v);

private:
    const static int UNMATCHED = -1;
    const int V;
    Bipartite_x bipartition;
    int cardinality;
    std::vector<int> mate;
    std::deque<bool> inMinVertexCover;
    std::deque<bool> marked;
    std::vector<int> distTo;

    std::string toString(std::vector<int>& path);

    bool isLevelGraphEdge(int v, int w);

    bool isResidualGraphEdge(int v, int w);

    bool hasAugmentingPath(Graph& G);

    void validate(int v);

    bool certifySolution(Graph& G);
};

#endif // HOPCROFT_KARP_H
