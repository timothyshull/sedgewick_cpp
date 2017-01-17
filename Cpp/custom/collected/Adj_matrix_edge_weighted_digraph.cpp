#include <sstream>
#include <vector>
#include <iomanip>

#include "Adj_matrix_edge_weighted_digraph.h"
#include "Directed_edge.h"
#include "Std_random.h"

Adj_matrix_edge_weighted_digraph::Adj_matrix_edge_weighted_digraph(unsigned num_vertices) : _num_vertices{num_vertices}
{
    _adjacency_matrix.reserve(num_vertices);
    for (int i = 0; i < _num_vertices; ++i) {
        _adjacency_matrix[i] = std::vector<Directed_edge_owning_pointer>(num_vertices);
        for (int j = 0; j < num_vertices; ++j) {
            _adjacency_matrix[i][j] = nullptr;
        }
    }
}

Adj_matrix_edge_weighted_digraph::Adj_matrix_edge_weighted_digraph(unsigned num_vertices, unsigned num_edges) : Adj_matrix_edge_weighted_digraph::Adj_matrix_edge_weighted_digraph(num_vertices)
{
    if (num_edges > num_vertices * num_vertices) {
        throw utility::Runtime_exception("The number of edges specified is too large");
    }

    int v;
    int w;
    double weight;
    for (int i = 0; i < num_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        weight = 100 * Std_random::uniform() / 100.0;
        add_edge(v, w, weight);
    }
}

//Directed_edge(4->6, weight: 0.71)
void Adj_matrix_edge_weighted_digraph::add_edge(Directed_edge& e)
{
    int v = e.from();
    int w = e.to();
    _check_vertex(v);
    _check_vertex(w);
    if (_adjacency_matrix[v][w] == nullptr) {
        ++_num_edges;
        _adjacency_matrix[v][w] = std::unique_ptr<Directed_edge>{new Directed_edge(e)};
    }
}

void Adj_matrix_edge_weighted_digraph::add_edge(int v, int w, double weight)
{
    _check_vertex(v);
    _check_vertex(w);
    if (_adjacency_matrix[v][w] == nullptr) {
        ++_num_edges;
        _adjacency_matrix[v][w] = std::unique_ptr<Directed_edge>{new Directed_edge(v, w, weight)};
    }
}

unsigned Adj_matrix_edge_weighted_digraph::num_vertices() const { return _num_vertices; }

unsigned Adj_matrix_edge_weighted_digraph::num_edges() const { return _num_edges; }

Adj_matrix_edge_weighted_digraph::Iterator_type Adj_matrix_edge_weighted_digraph::begin() noexcept
{
    return Adj_matrix_edge_weighted_digraph::Iterator_type(*this, 0, 0);
}

Adj_matrix_edge_weighted_digraph::Iterator_type Adj_matrix_edge_weighted_digraph::end() noexcept
{
    return Adj_matrix_edge_weighted_digraph::Iterator_type(*this);
}

std::string Adj_matrix_edge_weighted_digraph::to_string() const
{
    std::stringstream ss;
    ss << "Adj_matrix_edge_weighted_digraph(number of vertices: " << _num_vertices << ", number of edges: " << _num_edges << ",\n";
    for (int v = 0; v < _num_vertices; ++v) {
        ss << "    vertex " << std::setw(3) << v << ": ";
        for (int w = 0; w < _num_vertices; ++w) {
            auto e = _adjacency_matrix[v][w].get();
            std::string s;
            if (e == nullptr) {
                s = "null";
            } else {
                s = e->to_string();
            }
            utility::pad(s, 36, ' ');
            ss << s << ", ";
        }
        ss << "\n";
    }
    ss << ")";
    return ss.str();
}

inline bool operator==(const Adj_matrix_edge_weighted_digraph& x, const Adj_matrix_edge_weighted_digraph& y) { return x._adjacency_matrix == y._adjacency_matrix; }

inline bool operator!=(const Adj_matrix_edge_weighted_digraph& x, const Adj_matrix_edge_weighted_digraph& y) { return !(x == y); }

std::ostream& operator<<(std::ostream& os, const Adj_matrix_edge_weighted_digraph& out)
{
    return os << out.to_string();
}

void Adj_matrix_edge_weighted_digraph::_check_vertex(int v)
{
    if (v < 0 || v >= _num_vertices) {
        throw utility::Runtime_exception("Bad vertex value");
    }
}

Adj_iterator::Adj_iterator(Adj_matrix_edge_weighted_digraph& g)noexcept : _v{-1}, _w{-1}, _graph{g} {}

Adj_iterator::Adj_iterator(Adj_matrix_edge_weighted_digraph& g, int v)noexcept : _v{v}, _w{0}, _graph{g}
{
    _graph._check_vertex(v);
}

Adj_iterator::Adj_iterator(Adj_matrix_edge_weighted_digraph& g, int v, int w)noexcept : _v{v}, _w{w}, _graph{g}
{
    _graph._check_vertex(v);
    _graph._check_vertex(w);
}

Adj_iterator::Value_type Adj_iterator::operator*() const
{
    return _graph._adjacency_matrix[_v][_w].get();
}

// TODO: check this
Adj_iterator::Value_type Adj_iterator::operator->() const
{
    return _graph._adjacency_matrix[_v][_w].get();
}

Adj_iterator& Adj_iterator::operator++()
{
    if (_v == -1 || _w == -1) {
        throw utility::No_such_element_exception("Cannot iterate past end");
    }
    if (_w == _graph._num_vertices - 1 && _v == _graph._num_vertices - 1) {
        // at end
        _v = -1;
        _w = -1;
    } else if (_w == _graph._num_vertices - 1) {
        // at end of row -> move to next row and reset _w
        ++_v;
        _w = 0;
    } else {
        // move one column within same row
        ++_w;
    }
    return *this;
}

Adj_iterator Adj_iterator::operator++(int)
{
    Adj_iterator t{*this};
    ++(*this);
    return t;
}

Adj_iterator& Adj_iterator::operator--()
{
    if (_v == 0 || _w == 0) {
        throw utility::No_such_element_exception("Cannot decrement iterator before the start");
    }
    if (_v == -1 && _w == -1) {
        // at end
        _v = _graph._num_vertices - 1;
        _w = _graph._num_vertices - 1;
    } else if (_w == 0 && _v > 0) {
        --_v;
        _w = _graph._num_vertices - 1;
    } else {
        --_w;
    }
    return *this;
}

Adj_iterator Adj_iterator::operator--(int)
{
    Adj_iterator t{*this};
    --(*this);
    return t;
}

std::vector<Directed_edge_owning_pointer>& Adj_iterator::operator[](const int& index)
{
    return _graph._adjacency_matrix[index];
}

inline bool operator==(const Adj_iterator& x, const Adj_iterator& y) { return x._graph == y._graph && x._v == y._v && x._w == y._w; }

inline bool operator!=(const Adj_iterator& x, const Adj_iterator& y) { return !(x == y); }
