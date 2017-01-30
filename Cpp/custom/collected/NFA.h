#ifndef NFA_H
#define NFA_H

#include "Digraph.h"

class NFA {
public:
    NFA(std::string& regexp);

    bool recognizes(std::string& txt);

private:
    Digraph _graph;
    std::string _regexp;
    int _size;
};

#endif // NFA_H
