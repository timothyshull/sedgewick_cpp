#ifndef NFA_H
#define NFA_H

#include "Digraph.h"

class NFA {
public:
    NFA(std::string& regexp);

    bool recognizes(std::string& txt);

private:
    Digraph graph;
    std::string regexp;
    int m;
};

#endif // NFA_H
