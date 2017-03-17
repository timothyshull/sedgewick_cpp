#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

class Segment_tree;

class Segment_tree_node {
public:
    inline std::size_t size() const noexcept { return static_cast<std::size_t>(_to - _from + 1); }

private:
    int _sum;
    int _min;
    int _pending_val = std::numeric_limits<int>::max(); // default to check in _rsq
    int _from;
    int _to;

    friend class Segment_tree;
};

class Segment_tree {
public:
    Segment_tree() = default;

    Segment_tree(const Segment_tree&) = default;

    Segment_tree(Segment_tree&&) = default;

    ~Segment_tree() = default;

    Segment_tree& operator=(const Segment_tree&) = default;

    Segment_tree& operator=(Segment_tree&&) = default;

    Segment_tree(std::vector<int>& array);

    inline std::size_t size() const noexcept { return _array.size(); }

    int rsq(int from, int to);

    int r_min_q(int from, int to);

    void update(int from, int to, int value);

private:
    std::vector<Segment_tree_node> _heap;
    std::vector<int> _array;
    int _size;

    int _rsq(int v, int from, int to);

    void _build(int v, int from, int size);

    int _r_min_q(int v, int from, int to);

    void _update(int v, int from, int to, int value);

    void _propagate(int v);

    void _change(Segment_tree_node& n, int value);

    inline bool _contains(int from1, int to1, int from2, int to2) const noexcept { return from2 >= from1 && to2 <= to1; }

    inline bool _intersects(int from1, int to1, int from2, int to2) const noexcept { return from1 <= from2 && to1 >= from2 || from1 >= from2 && from1 <= to2; }
};

#endif // SEGMENT_TREE_H
