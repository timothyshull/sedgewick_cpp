// Program 4.9 - Equivalence relations ADT interface
#ifndef EQUIVALENCE_RELATIONS_H
#define EQUIVALENCE_RELATIONS_H

#include <vector>

class Union_find {
public:

    Union_find(std::size_t size);

    inline bool find(int p, int q) const { return _find(p) == _find(q); };

    void unite(int p, int q);

private:
private:
    std::vector<int> _id;
    std::vector<int> _size;

    int _find(int x) const;
};

#endif // EQUIVALENCE_RELATIONS_H
