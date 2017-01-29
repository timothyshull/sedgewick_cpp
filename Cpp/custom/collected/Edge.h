#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
public:
    Edge() = default;

    Edge(const Edge&) = default;

    Edge(Edge&&) = default;

    ~Edge() = default;

    Edge& operator=(const Edge&) = default;

    Edge& operator=(Edge&&) = default;

    Edge(int v, int w, double weight);

    inline double weight() const noexcept { return _weight; }

    inline int either() const noexcept { return _v; }

    int other(int vertex);

    inline bool operator<(const Edge& rhs) const noexcept { return _weight < rhs._weight; }

    inline bool operator==(const Edge& rhs) const noexcept { return _v == rhs._v && _w == rhs._w && _weight == rhs._weight; }

    inline bool operator!=(const Edge& rhs) const noexcept { return !(*this == rhs); }

    std::string to_string() { return "Edge(source: " + std::to_string(_v) + ", destination: " + std::to_string(_w) + ", weight: " + std::to_string(_weight) + ")"; }

private:
    const int _v;
    const int _w;
    const double _weight;
};

std::ostream& operator<<(std::ostream& os, Edge& out);

#endif // EDGE_H
