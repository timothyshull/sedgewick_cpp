#ifndef QUICK_UNION_UF_H
#define QUICK_UNION_UF_H

#include <vector>

class Quick_union_uf {
public:
    Quick_union_uf(int n);

    int count();

    int find(int p);

    bool connected(int p, int q);

    void create_union(int p, int q);;
private:
    std::vector<int> parent;
    int count;

    void validate(int p);
};

#endif // QUICK_UNION_UF_H
