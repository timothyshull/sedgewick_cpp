#ifndef TRANSITIVE_CLOSURE_H
#define TRANSITIVE_CLOSURE_H

#include "Directed_dfs.h"

class Transitive_closure {
public:
    Transitive_closure(Digraph& digraph);

    inline bool reachable(int v, int w) const { return _tc[v].marked(w); }

private:
    std::vector<Directed_dfs> _tc;
};

#endif // TRANSITIVE_CLOSURE_H
