#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>

class Fenwick_tree {
public:
    Fenwick_tree() = default;

    Fenwick_tree(const Fenwick_tree&) = default;

    Fenwick_tree(Fenwick_tree&&) = default;

    ~Fenwick_tree() = default;

    Fenwick_tree& operator=(const Fenwick_tree&) = default;

    Fenwick_tree& operator=(Fenwick_tree&&) = default;

    explicit Fenwick_tree(int size);

    int rsq(int index);

    int rsq(int a, int b);

    void update(int index, int value);

    inline int size() const { return _vector.size() - 1; }

private:
    std::vector<int> _vector;
};

#endif // FENWICK_TREE_H
