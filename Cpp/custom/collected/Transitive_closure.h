#ifndef TRANSITIVE_CLOSURE_H
#define TRANSITIVE_CLOSURE_H

#include "Directed_dfs.h"

class Transitive_closure {
public:
    Transitive_closure(Digraph& G);

    bool reachable(int v, int w);

private:
    std::vector<Directed_dfs> tc;
};

#endif // TRANSITIVE_CLOSURE_H
