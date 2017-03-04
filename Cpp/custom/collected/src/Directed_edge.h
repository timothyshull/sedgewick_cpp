#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H

#include <cmath>

#include "utility.h"

class Directed_edge {
public:
    Directed_edge();

    Directed_edge(const Directed_edge&) = default;

    Directed_edge(Directed_edge&&) = default;

    ~Directed_edge() = default;

    Directed_edge& operator=(const Directed_edge&) = default;

    Directed_edge& operator=(Directed_edge&&) = default;

    Directed_edge(int source, int destination, double weight);

    inline int from() const noexcept { return _source; }

    inline int to() const noexcept { return _destination; }

    inline double weight() const noexcept { return _weight; }

    std::string to_string() const;

    inline bool operator==(const Directed_edge& rhs) const noexcept { return _source == rhs._source && _destination == rhs._destination && _weight == rhs._weight; }

    inline bool operator!=(const Directed_edge& rhs) const noexcept { return !(rhs == *this); }

private:
    int _source;
    int _destination;
    double _weight;
};

std::ostream& operator<<(std::ostream& os, const Directed_edge& out);

#endif // DIRECTED_EDGE_H
