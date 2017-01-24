#ifndef DIRECTED_CYCLE_X_H
#define DIRECTED_CYCLE_X_H

#include <vector>
#include "Stack.h"

class Directed_cycle_x {
public:
    Directed_cycle_x(Digraph& G);
    std::vector<int> cycle();
    bool has_cycle();
private:
    Stack<int> cycle;
    bool check();
};

#endif // DIRECTED_CYCLE_X_H
