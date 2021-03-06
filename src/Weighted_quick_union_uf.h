#ifndef WEIGHTED_QUICK_UNION_UF_H
#define WEIGHTED_QUICK_UNION_UF_H

#include <vector>

class Weighted_quick_union_uf {
public:
    explicit Weighted_quick_union_uf(int n);

    int count() const noexcept
    {
        return _count;
    }

    int find(int p) const;

    inline bool connected(int p, int q) const { return find(p) == find(q); };

    void create_union(int p, int q); // union is a C++ keyword

private:
    std::vector<int> _parent;
    std::vector<int> _size;
    int _count;

    void _validate(int p) const;
};

#endif // WEIGHTED_QUICK_UNION_UF_H
