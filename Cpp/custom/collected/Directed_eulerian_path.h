#ifndef DIRECTED_EULERIAN_PATH_H
#define DIRECTED_EULERIAN_PATH_H

#include "Stack.h"
#include "Digraph.h"

class Directed_eulerian_path {
public:
    Directed_eulerian_path(Digraph& digraph);

    inline Stack<int> path() const { return _path; }

    inline bool has_eulerian_path() const { return !_path.is_empty(); }

    static void unit_test(Digraph& digraph, std::string&& description);
private:
    Stack<int> _path;

    int _non_isolated_vertex(Digraph& digraph);

    bool _has_eulerian_path(Digraph& digraph);

    bool _check(Digraph& digraph);

};

#endif // DIRECTED_EULERIAN_PATH_H
