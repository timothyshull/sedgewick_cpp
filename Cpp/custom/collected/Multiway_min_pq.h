#ifndef MULTIWAY_MIN_PQ_H
#define MULTIWAY_MIN_PQ_H

#include <vector>

template<typename Key, typename Comparator = std::less<Key>>
class Multiway_min_pq {
public:
    Multiway_min_pq(int D)
    {
        if (D < 2) { throw utility::Illegal_argument_exception("Dimension should be 2 or over"); }
        this.d = D;
        order = 1;
        keys = (Key[]) new Comparable[D << 1];
        comp = new MyComparator();
    }

    Multiway_min_pq(std::vector<Key>& a, int D)
    {
        if (D < 2) { throw utility::Illegal_argument_exception("Dimension should be 2 or over"); }
        this.d = D;
        order = 1;
        keys = (Key[]) new Comparable[D << 1];
        comp = new MyComparator();
        for (Key k : a) { insert(k); }
    }

    bool is_empty() { return n == 0; };

    int size() { return n; }

    void insert(Key& key) {
        keys[n + d] = key;
        swim(n++);
        if (n == keys.size() - d) {
            resize(getN(order + 1) + d);
            order++;
        }
    }
    Key minKey() {
        if (is_empty()) throw new NoSuchElementException("Priority queue is empty");
        return keys[d];
    }

    Key delMin() {
        if (is_empty()) throw new NoSuchElementException("Priority queue is empty");
        exch(0, --n);
        sink(0);
        Key min = keys[n + d];
        keys[n + d] = null;
        int number = getN(order - 2);
        if (order > 1 && n == number) {
            resize(number + (int) std::pow(d, order - 1) + d);
            order--;
        }
        return min;
    }

private:
    const int d;
    int n;
    int order;
    std::vector<Key> keys;
    const Comparator comp;

    bool greater(int x, int y) {
        int i = x + d, j = y + d;
        if (keys[i] == null) return false;
        if (keys[j] == null) return true;
        return comp.compare(keys[i], keys[j]) > 0;
    }

    void exch(int x, int y) {
        int i = x + d, j = y + d;
        Key swap = keys[i];
        keys[i] = keys[j];
        keys[j] = swap;
    }

    int getN(int order) {
        return (1 - ((int) std::pow(d, order + 1))) / (1 - d);
    }

    void swim(int i) {
        if (i > 0 && greater((i - 1) / d, i)) {
            exch(i, (i - 1) / d);
            swim((i - 1) / d);
        }
    }

    void sink(int i) {
        int child = d * i + 1;
        if (child >= n) return;
        int min = minChild(i);
        while (min < n && greater(i, min)) {
            exch(i, min);
            i = min;
            min = minChild(i);
        }
    }

    int minChild(int i) {
        int loBound = d * i + 1, hiBound = d * i + d;
        int min = loBound;
        for (int cur = loBound; cur <= hiBound; ++cur) {
            if (cur < n && greater(min, cur)) min = cur;
        }
        return min;
    }

    void resize(int N) {
        Key[] array = (Key[]) new Comparable[N];
        for (int i = 0; i < std::min(keys.length, array.length); ++i) {
            array[i] = keys[i];
            keys[i] = null;
        }
        keys = array;
    }

};

#endif // MULTIWAY_MIN_PQ_H
