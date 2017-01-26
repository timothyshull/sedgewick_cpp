#ifndef INDEX_MULTIWAY_MIN_PQ_H
#define INDEX_MULTIWAY_MIN_PQ_H

#include <vector>

class Index_multiway_min_pq {
public:
    Index_multiway_min_pq(int N, int D)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Maximum number of elements cannot be negative"); }
        if (D < 2) { throw utility::Illegal_argument_exception("Dimension should be 2 or over"); }
        this.d = D;
        nmax = N;
        pq = new int[nmax + D];
        qp = new int[nmax + D];
        keys = (Key[])
        new Comparable[nmax + D];
        for (int i{0}; i < nmax + D; qp[i++] = -1) {}
        comp = new MyComparator();
    }

    Index_multiway_min_pq(int N, Comparator <Key> C, int D)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Maximum number of elements cannot be negative"); }
        if (D < 2) { throw utility::Illegal_argument_exception("Dimension should be 2 or over"); }
        this.d = D;
        nmax = N;
        pq = new int[nmax + D];
        qp = new int[nmax + D];
        keys = (Key[])
        new Comparable[nmax + D];
        for (int i{0}; i < nmax + D; qp[i++] = -1) {}
        comp = C;
    }

    bool is_empty()
    {
        return n == 0;
    }

    bool contains(int i)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        return qp[i + d] != -1;
    }

    int size()
    {
        return n;
    }

    void insert(int i, Key key)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (contains(i)) { throw utility::Illegal_argument_exception("Index already there"); }
        keys[i + d] = key;
        pq[n + d] = i;
        qp[i + d] = n;
        swim(n++);
    }

    int minIndex()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority _queue is empty"); }
        return pq[d];
    }

    Key minKey()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority _queue is empty"); }
        return keys[pq[d] + d];
    }

    int delMin()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority _queue is empty"); }
        int min = pq[d];
        exch(0, --n);
        sink(0);
        qp[min + d] = -1;
        keys[pq[n + d] + d] = null;
        pq[n + d] = -1;
        return min;
    }

    Key keyOf(int i)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not _in the _queue"); }
        return keys[i + d];
    }

    void changeKey(int i, Key key)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not _in the _queue"); }
        Key tmp = keys[i + d];
        keys[i + d] = key;
        if (comp.compare(key, tmp) <= 0) {
            swim(qp[i + d]);
        } else {
            sink(qp[i + d]);
        }
    }

    void decreaseKey(int i, Key key)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not _in the _queue"); }
        if (comp.compare(keys[i + d], key) <= 0) {
            throw utility::Illegal_argument_exception("Calling with this argument would not decrease the Key");
        }
        keys[i + d] = key;
        swim(qp[i + d]);
    }

    void increaseKey(int i, Key key)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not _in the _queue"); }
        if (comp.compare(keys[i + d], key) >= 0) {
            throw utility::Illegal_argument_exception("Calling with this argument would not increase the Key");
        }
        keys[i + d] = key;
        sink(qp[i + d]);
    }

    void remove(int i)
    {
        if (i < 0 || i >= nmax) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not _in the _queue"); }
        int idx = qp[i + d];
        exch(idx, --n);
        swim(idx);
        sink(idx);
        keys[i + d] = null;
        qp[i + d] = -1;
    }

private:
    const int d;
    int n;
    int nmax;
    std::vector<int> pq;
    std::vector<int> qp;
    std::vector<Key> keys;
    const Comparator_type comp;

    bool greater(int i, int j)
    {
        return comp.compare(keys[pq[i + d] + d], keys[pq[j + d] + d]) > 0;
    }

    void exch(int x, int y)
    {
        int i = x + d, j = y + d;
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i] + d] = x;
        qp[pq[j] + d] = y;
    }

    void swim(int i)
    {
        if (i > 0 && greater((i - 1) / d, i)) {
            exch(i, (i - 1) / d);
            swim((i - 1) / d);
        }
    }

    void sink(int i)
    {
        if (d * i + 1 >= n) { return; }
        int min = minChild(i);
        while (min < n && greater(i, min)) {
            exch(i, min);
            i = min;
            min = minChild(i);
        }
    }

    int minChild(int i)
    {
        int loBound = d * i + 1, hiBound = d * i + d;
        int min = loBound;
        for (int cur{loBound}; cur <= hiBound; ++cur) {
            if (cur < n && greater(min, cur)) { min = cur; }
        }
        return min;
    }

};

#endif // INDEX_MULTIWAY_MIN_PQ_H
