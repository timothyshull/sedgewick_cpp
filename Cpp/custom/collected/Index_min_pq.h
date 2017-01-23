#ifndef INDEX_MIN_PQ_H
#define INDEX_MIN_PQ_H

#include <memory>
#include <vector>

template<typename Key>
class Index_min_pq_node;

template<typename Key>
class Index_min_pq_iterator;

template<typename Key>
class Index_min_pq_reverse_iterator;

template<typename T>
struct Index_min_pq_key_comparator;

template<typename Key, typename Comparator = Index_min_pq_key_comparator<Key>>
class Index_min_pq;

template<typename Key>
struct Index_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Index_min_pq_node<Key_type>;
    using Node_raw_pointer = Index_min_pq_node<Key_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key, typename Value>
class Index_min_pq_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Index_min_pq_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Index_min_pq<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Index_min_pq_iterator() noexcept = delete;

    explicit Index_min_pq_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Index_min_pq_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
        if (index > _in_order.size()) {
            throw utility::Illegal_argument_exception("The index is out of range");
        }
    }

    inline Node_raw_pointer operator*() const
    {
        return _in_order[_index];
    }

    inline Node_raw_pointer operator->() const
    {
        return _in_order[_index];
    }

    inline Index_min_pq_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Index_min_pq_iterator operator++(int)
    {
        Index_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Index_min_pq_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Index_min_pq_iterator operator--(int)
    {
        Index_min_pq_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Index_min_pq_iterator& x, const Index_min_pq_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Index_min_pq_iterator& x, const Index_min_pq_iterator& y) { return !(x == y); }

private:
    template<typename>
    friend class Index_min_pq;
};

template<typename T>
struct Index_min_pq_key_comparator {
    int operator()(const T& x, const T& y) const
    {
        if (x < y) {
            return -1;
        } else if (y < x) {
            return 1;
        }
        return 0;
    }
};

template<typename Key, typename Value, typename Comparator>
class Index_min_pq {
public:
    using Node_traits = Index_min_pq_node_pointer_traits<Key>;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_key_pointer = typename Node_traits::Shared_key_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Comparator_type = Comparator;

    using Reference_type = Value_type&;
    using Const_reference_type = const Value_type&;
    using Pointer_type = Value_type*;
    using Const_pointer_type = Value_type const*;
    using Size_type = std::size_t;
    using Difference_type = std::ptrdiff_t;  // TODO: check on this because of the relationship with max_size
    using Iterator_type = Index_min_pq_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Index_min_pq_reverse_iterator<Key_type, Value_type>;

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

    Index_min_pq(int maxN)
    {
        if (maxN < 0) { throw new IllegalArgumentException(); }
        this.maxN = maxN;
        n = 0;
        keys = (Key[]) new Comparable[maxN + 1];    // make this of length maxN??
        pq = new int[maxN + 1];
        qp = new int[maxN + 1];                   // make this of length maxN??
        for (int i = 0; i <= maxN; i++) {
            qp[i] = -1;
        }
    }

    boolean isEmpty()
    {
        return n == 0;
    }

    boolean contains(int i)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        return qp[i] != -1;
    }

    int size()
    {
        return n;
    }

    void insert(int i, Key key)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (contains(i)) { throw new IllegalArgumentException("index is already in the priority queue"); }
        n++;
        qp[i] = n;
        pq[n] = i;
        keys[i] = key;
        swim(n);
    }

    int minIndex()
    {
        if (n == 0) { throw new NoSuchElementException("Priority queue underflow"); }
        return pq[1];
    }

    Key minKey()
    {
        if (n == 0) { throw new NoSuchElementException("Priority queue underflow"); }
        return keys[pq[1]];
    }

    int delMin()
    {
        if (n == 0) { throw new NoSuchElementException("Priority queue underflow"); }
        int min = pq[1];
        exch(1, n--);
        sink(1);
        assert
        min == pq[n + 1];
        qp[min] = -1;        // delete
        keys[min] = null;    // to help with garbage collection
        pq[n + 1] = -1;        // not needed
        return min;
    }

    Key keyOf(int i)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("index is not in the priority queue"); }
        else { return keys[i]; }
    }

    void changeKey(int i, Key key)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("index is not in the priority queue"); }
        keys[i] = key;
        swim(qp[i]);
        sink(qp[i]);
    }

    void change(int i, Key key)
    {
        changeKey(i, key);
    }

    void decreaseKey(int i, Key key)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("index is not in the priority queue"); }
        if (keys[i].compareTo(key) <= 0) {
            throw new IllegalArgumentException("Calling decreaseKey() with given argument would not strictly decrease the key");
        }
        keys[i] = key;
        swim(qp[i]);
    }

    void increaseKey(int i, Key key)
    {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("index is not in the priority queue"); }
        if (keys[i].compareTo(key) >= 0) {
            throw new IllegalArgumentException("Calling increaseKey() with given argument would not strictly increase the key");
        }
        keys[i] = key;
        sink(qp[i]);
    }

    void delete(
    int i
    ) {
        if (i < 0 || i >= maxN) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("index is not in the priority queue"); }
        int index = qp[i];
        exch(index, n--);
        swim(index);
        sink(index);
        keys[i] = null;
        qp[i] = -1;
    }

private:
    int maxN;
    int n;
    std::vector<int> pq;
    std::vector<int> qp;
    std::vector<Key> keys;

    template<typename, typename>
    friend class Index_min_pq_iterator;

    template<typename, typename>
    friend class Index_min_pq_reverse_iterator;

    boolean greater(int i, int j)
    {
        return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
    }

    void exch(int i, int j)
    {
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    void swim(int k)
    {
        while (k > 1 && greater(k / 2, k)) {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k)
    {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && greater(j, j + 1)) { j++; }
            if (!greater(k, j)) { break; }
            exch(k, j);
            k = j;
        }
    }
};

#endif // INDEX_MIN_PQ_H
