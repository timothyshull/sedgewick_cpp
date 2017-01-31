#ifndef DIRECTED_CYCLE_X_H
#define DIRECTED_CYCLE_X_H

#include <vector>
#include "Stack.h"
#include "Digraph.h"

class Directed_cycle_x {
public:
    Directed_cycle_x(Digraph& digraph);

    inline Stack<int> cycle() const { return _cycle; }

    inline bool has_cycle() const { return !_cycle.is_empty(); }

private:
    Stack<int> _cycle;

    bool _check();
};

#endif // DIRECTED_CYCLE_X_H
