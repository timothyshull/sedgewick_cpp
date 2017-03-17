#ifndef QUICK_UNION_UF_H
#define QUICK_UNION_UF_H

#include <vector>

class Quick_union_uf {
public:
    Quick_union_uf(int n);

    inline int count() const noexcept { return _count; }

    int find(int p);

    inline bool connected(int p, int q) { return find(p) == find(q); }

    void create_union(int p, int q);;
private:
    std::vector<int> _parent;
    int _count;

    void _validate(int p);
};

#endif // QUICK_UNION_UF_H
