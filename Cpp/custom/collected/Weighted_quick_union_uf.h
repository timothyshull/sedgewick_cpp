#ifndef WEIGHTED_QUICK_UNION_UF_H
#define WEIGHTED_QUICK_UNION_UF_H

#include <vector>

class Weighted_quick_union_uf {
public:
    explicit Weighted_quick_union_uf(int n);

    inline int count() const { return _count; }

    int find(int p) const;

    bool connected(int p, int q) const;

    void create_union(int p, int q); // union is a C++ keyword
private:
    std::vector<int> _parent;
    std::vector<int> _size;
    int _count;

    void _validate(int p) const;
};

#endif // WEIGHTED_QUICK_UNION_UF_H
