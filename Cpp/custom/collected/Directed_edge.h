#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H

#include <cmath>

#include "utility.h"

class Directed_edge {
private:
    unsigned _source;
    unsigned _destination;
    double _weight;

public:
    Directed_edge(unsigned source, unsigned destination, double weight);

    Directed_edge() = default;

    ~Directed_edge() = default;

    Directed_edge(const Directed_edge&) = default;

    Directed_edge& operator=(const Directed_edge&) = default;

    Directed_edge(Directed_edge&&) = default;

    Directed_edge& operator=(Directed_edge&&) = default;

    inline int from() const { return _source; }

    inline int to() const { return _destination; }

    inline double weight() const { return _weight; }

    std::string to_string() const;
};

std::ostream& operator<<(std::ostream& os, const Directed_edge& out);

#endif //DIRECTED_EDGE_H
