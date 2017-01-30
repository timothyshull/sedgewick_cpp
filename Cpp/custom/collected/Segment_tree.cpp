#include <cmath>

#include "Segment_tree.h"

Segment_tree::Segment_tree(std::vector<int>& array)
        : _array{array},
          _size{static_cast<int>(2 * std::pow(2.0, std::floor((std::log(static_cast<double>(array.size())) / std::log(2.0)) + 1)))},
          _heap(static_cast<std::vector<Segment_tree_node>::size_type>(_size))
{
    _build(1, 0, static_cast<int>(array.size()));
}

int Segment_tree::rsq(int from, int to)
{
    return _rsq(1, from, to);
}

int Segment_tree::r_min_q(int from, int to)
{
    return _r_min_q(1, from, to);
}

void Segment_tree::update(int from, int to, int value)
{
    _update(1, from, to, value);
}

int Segment_tree::_rsq(int v, int from, int to)
{
    Segment_tree_node n = _heap[v];

    if (n._pending_val != std::numeric_limits<int>::max() && _contains(n._from, n._to, from, to)) {
        return (to - from + 1) * n._pending_val;
    }

    if (_contains(from, to, n._from, n._to)) {
        return _heap[v]._sum;
    }

    if (_intersects(from, to, n._from, n._to)) {
        _propagate(v);
        int left_sum{_rsq(2 * v, from, to)};
        int right_sum{_rsq(2 * v + 1, from, to)};

        return left_sum + right_sum;
    }

    return 0;
}

void Segment_tree::_build(int v, int from, int size)
{
    _heap[v] = Segment_tree_node{};
    _heap[v]._from = from;
    _heap[v]._to = from + size - 1;

    if (size == 1) {
        _heap[v]._sum = _array[from];
        _heap[v]._min = _array[from];
    } else {
        _build(2 * v, from, size / 2);
        _build(2 * v + 1, from + size / 2, size - size / 2);

        _heap[v]._sum = _heap[2 * v]._sum + _heap[2 * v + 1]._sum;
        _heap[v]._min = std::min(_heap[2 * v]._min, _heap[2 * v + 1]._min);
    }
}

int Segment_tree::_r_min_q(int v, int from, int to)
{
    Segment_tree_node n = _heap[v];

    if (n._pending_val != std::numeric_limits<int>::max() && _contains(n._from, n._to, from, to)) {
        return n._pending_val;
    }

    if (_contains(from, to, n._from, n._to)) {
        return _heap[v]._min;
    }

    if (_intersects(from, to, n._from, n._to)) {
        _propagate(v);
        int left_min{_r_min_q(2 * v, from, to)};
        int right_min{_r_min_q(2 * v + 1, from, to)};

        return std::min(left_min, right_min);
    }

    return std::numeric_limits<int>::max();
}

void Segment_tree::_update(int v, int from, int to, int value)
{
    Segment_tree_node n = _heap[v];

    if (_contains(from, to, n._from, n._to)) {
        _change(n, value);
    }

    if (n.size() == 1) { return; }

    if (_intersects(from, to, n._from, n._to)) {
        _propagate(v);

        _update(2 * v, from, to, value);
        _update(2 * v + 1, from, to, value);

        n._sum = _heap[2 * v]._sum + _heap[2 * v + 1]._sum;
        n._min = std::min(_heap[2 * v]._min, _heap[2 * v + 1]._min);
    }
}

void Segment_tree::_propagate(int v)
{
    Segment_tree_node n = _heap[v];

    if (n._pending_val != std::numeric_limits<int>::max()) {
        _change(_heap[2 * v], n._pending_val);
        _change(_heap[2 * v + 1], n._pending_val);
        // n._pending_val = std::numeric_limits<int>::max();
    }
}

void Segment_tree::_change(Segment_tree_node& n, int value)
{
    n._pending_val = value;
    n._sum = static_cast<int>(n.size() * value);
    n._min = value;
    _array[n._from] = value;
}
