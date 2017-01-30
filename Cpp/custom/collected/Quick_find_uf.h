#ifndef QUICK_FIND_UF_H
#define QUICK_FIND_UF_H

#include <vector>

class Quick_find_uf {
public:
    Quick_find_uf(int n);

    inline int count() const noexcept { return _count; }

    int find(int p);

    bool connected(int p, int q);

    void create_union(int p, int q);

private:
    std::vector<int> _id;
    int _count;

    void _validate(int p);
};

#endif // QUICK_FIND_UF_H
