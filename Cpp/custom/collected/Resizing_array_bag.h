#ifndef RESIZING_ARRAY_BAG_H
#define RESIZING_ARRAY_BAG_H

#include <vector>

template <typename T>
class Resizing_array_bag_iterator {

};

template <typename T>
class Resizing_array_bag {
public:
    Resizing_array_bag() {
        a = (Item[]) new Object[2];
        n = 0;
    }
    bool is_empty() {
        return n == 0;
    }
    int size() {
        return n;
    }

    void add(T& item) {
        if (n == a.length) resize(2 * a.length);
        a[n++] = item;
    }
private:
    std::vector<T> a;
    int n;

void resize(int capacity) {
        assert capacity >= n;
        Item[] temp = (Item[]) new Object[capacity];
        for (int i{0}; i < n; ++i)
            temp[i] = a[i];
        a = temp;
    }
};

#endif // RESIZING_ARRAY_BAG_H
