#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
public:
    Edge(int v, int w, double weight);

    double weight();

    int either();

    int other(int vertex);

    bool operator<(Edge& rhs);

    std::string to_string();

private:
    const int v;
    const int w;
    const double weight;
};

std::ostream& operator<<(std::ostream& os, Edge& out);

#endif // EDGE_H
