#ifndef INDEX_BINOMIAL_MIN_PQ_H
#define INDEX_BINOMIAL_MIN_PQ_H

#include <memory>

template<typename Key>
class Index_binomial_min_pq_node;

template<typename Key>
class Index_binomial_min_pq_iterator;

template<typename Key>
class Index_binomial_min_pq_reverse_iterator;

template<typename T>
struct Index_binomial_min_pq_key_comparator;

template<typename Key, typename Comparator = Index_binomial_min_pq_key_comparator<Key>>
class Index_binomial_min_pq;

template<typename Key>
struct Index_binomial_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Index_binomial_min_pq_node<Key_type>;
    using Node_raw_pointer = Index_binomial_min_pq_node<Key_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key>
class Index_binomial_min_pq_node {
public:
    using Node_traits = Index_binomial_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = typename Node_traits::Size_type;

private:
    Shared_key_pointer key;
    int order;
    int index;
    Node_owning_pointer parent;
    Node_owning_pointer child;
    Node_owning_pointer sibling;

    template<typename, typename, typename>
    friend class Index_binomial_min_pq;

    template<typename, typename>
    friend class Index_binomial_min_pq_iterator;

    template<typename, typename>
    friend class Index_binomial_min_pq_reverse_iterator;
};

template<typename Key, typename Value>
class Index_binomial_min_pq_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Index_binomial_min_pq_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Index_binomial_min_pq<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Index_binomial_min_pq_iterator() noexcept = delete;

    explicit Index_binomial_min_pq_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Index_binomial_min_pq_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
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

    inline Index_binomial_min_pq_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Index_binomial_min_pq_iterator operator++(int)
    {
        Index_binomial_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Index_binomial_min_pq_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Index_binomial_min_pq_iterator operator--(int)
    {
        Index_binomial_min_pq_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Index_binomial_min_pq_iterator& x, const Index_binomial_min_pq_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Index_binomial_min_pq_iterator& x, const Index_binomial_min_pq_iterator& y) { return !(x == y); }

private:
    template<typename>
    friend class Index_binomial_min_pq;
};

template<typename T>
struct Index_binomial_min_pq_key_comparator {
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
class Index_binomial_min_pq {
public:
    using Node_traits = Index_binomial_min_pq_node_pointer_traits<Key>;
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
    using Iterator_type = Index_binomial_min_pq_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Index_binomial_min_pq_reverse_iterator<Key_type, Value_type>;

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

    Index_binomial_min_pq(int N)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Cannot create a priority queue of negative size"); }
        comparator = new MyComparator();
        nodes = (Node<Key>[])
        new Node[N];
        this.n = N;
    }

    Index_binomial_min_pq(int N, Comparator<Key> comparator)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Cannot create a priority queue of negative size"); }
        this.comparator = comparator;
        nodes = (Node<Key>[])
        new Node[N];
        this.n = N;
    }

    bool is_empty()
    {
        return head == null;
    }

    bool contains(int i)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        else { return nodes[i] != null; }
    }

    int size()
    {
        int result = 0, tmp;
        for (Node <Key> node = head; node != null; node = node.sibling) {
            if (node.order > 30) {
                throw new ArithmeticException("The number of elements cannot be evaluated, but the priority queue is still valid.");
            }
            tmp = 1 << node.order;
            result |= tmp;
        }
        return result;
    }

    void insert(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (contains(i)) { throw utility::Illegal_argument_exception("Specified index is already in the queue"); }
        Node <Key> x = new Node<Key>();
        x.key = key;
        x.index = i;
        x.order = 0;
        nodes[i] = x;
        IndexBinomialMinPQ <Key> H = new IndexBinomialMinPQ<Key>();
        H.head = x;
        head =
        union(H).head;
    }

    int minIndex()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        Node <Key> min = head;
        Node <Key> current = head;
        while (current.sibling != null) {
            min = (greater(min.key, current.sibling.key)) ? current.sibling : min;
            current = current.sibling;
        }
        return min.index;
    }

    Key minKey()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        Node <Key> min = head;
        Node <Key> current = head;
        while (current.sibling != null) {
            min = (greater(min.key, current.sibling.key)) ? current.sibling : min;
            current = current.sibling;
        }
        return min.key;
    }

    int delMin()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        Node <Key> min = eraseMin();
        Node <Key> x = (min.child == null) ? min : min.child;
        if (min.child != null) {
            min.child = null;
            Node <Key> prevx = null, nextx = x.sibling;
            while (nextx != null) {
                x.parent = null; // for garbage collection
                x.sibling = prevx;
                prevx = x;
                x = nextx;
                nextx = nextx.sibling;
            }
            x.parent = null;
            x.sibling = prevx;
            IndexBinomialMinPQ <Key> H = new IndexBinomialMinPQ<Key>();
            H.head = x;
            head =
            union(H).head;
        }
        return min.index;
    }

    Key keyOf(int i)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw utility::Illegal_argument_exception("Specified index is not in the queue"); }
        return nodes[i].key;
    }

    void changeKey(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw utility::Illegal_argument_exception("Specified index is not in the queue"); }
        if (greater(nodes[i].key, key)) { decreaseKey(i, key); }
        else { increaseKey(i, key); }
    }

    void decreaseKey(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not in the queue"); }
        if (greater(key, nodes[i].key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not decrease the key");
        }
        Node <Key> x = nodes[i];
        x.key = key;
        swim(i);
    }

    void increaseKey(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not in the queue"); }
        if (greater(nodes[i].key, key)) {
            throw utility::Illegal_argument_exception("Calling with this argument would not increase the key");
        }
        delete (i);
        insert(i, key);
    }

    void remove(int i)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not in the queue"); }
        toTheRoot(i);
        Node <Key> x = erase(i);
        if (x.child != null) {
            Node <Key> y = x;
            x = x.child;
            y.child = null;
            Node <Key> prevx = null, nextx = x.sibling;
            while (nextx != null) {
                x.parent = null;
                x.sibling = prevx;
                prevx = x;
                x = nextx;
                nextx = nextx.sibling;
            }
            x.parent = null;
            x.sibling = prevx;
            IndexBinomialMinPQ <Key> H = new IndexBinomialMinPQ<Key>();
            H.head = x;
            head =
            union(H).head;
        }
    }

private:
    Node_owning_pointer head;
    std::vector<Raw_node_pointer> nodes;
    int n;
    Comparator_type comp;

    template<typename, typename>
    friend class Index_binomial_min_pq_iterator;

    template<typename, typename>
    friend class Index_binomial_min_pq_reverse_iterator;

    bool greater(Key n, Key m)
    {
        if (n == null) { return false; }
        if (m == null) { return true; }
        return comparator.compare(n, m) > 0;
    }

    void exchange(Node <Key> x, Node <Key> y)
    {
        Key tempKey = x.key;
        x.key = y.key;
        y.key = tempKey;
        int tempInt = x.index;
        x.index = y.index;
        y.index = tempInt;
        nodes[x.index] = x;
        nodes[y.index] = y;
    }

    void link(Node <Key> root1, Node <Key> root2)
    {
        root1.sibling = root2.child;
        root1.parent = root2;
        root2.child = root1;
        root2.order++;
    }

    void swim(int i)
    {
        Node <Key> x = nodes[i];
        Node <Key> parent = x.parent;
        if (parent != null && greater(parent.key, x.key)) {
            exchange(x, parent);
            swim(i);
        }
    }

    void toTheRoot(int i)
    {
        Node <Key> x = nodes[i];
        Node <Key> parent = x.parent;
        if (parent != null) {
            exchange(x, parent);
            toTheRoot(i);
        }
    }

    Node <Key> erase(int i)
    {
        Node <Key> reference = nodes[i];
        Node <Key> x = head;
        Node <Key> previous = null;
        while (x != reference) {
            previous = x;
            x = x.sibling;
        }
        previous.sibling = x.sibling;
        if (x == head) { head = head.sibling; }
        nodes[i] = null;
        return x;
    }

    Node <Key> eraseMin()
    {
        Node <Key> min = head;
        Node <Key> previous = null;
        Node <Key> current = head;
        while (current.sibling != null) {
            if (greater(min.key, current.sibling.key)) {
                previous = current;
                min = current.sibling;
            }
            current = current.sibling;
        }
        previous.sibling = min.sibling;
        if (min == head) { head = min.sibling; }
        nodes[min.index] = null;
        return min;
    }

    Node <Key> merge(Node <Key> h, Node <Key> x, Node <Key> y)
    {
        if (x == null && y == null) { return h; }
        else if (x == null) { h.sibling = merge(y, null, y.sibling); }
        else if (y == null) { h.sibling = merge(x, x.sibling, null); }
        else if (x.order < y.order) { h.sibling = merge(x, x.sibling, y); }
        else { h.sibling = merge(y, x, y.sibling); }
        return h;
    }

    IndexBinomialMinPQ <Key> union(IndexBinomialMinPQ<Key>
    heap) {
        this.head = merge(new Node<Key>(), this.head, heap.head).sibling;
        Node <Key> x = this.head;
        Node <Key> prevx = null, nextx = x.sibling;
        while (nextx != null) {
            if (x.order < nextx.order ||
                (nextx.sibling != null && nextx.sibling.order == x.order)) {
                prevx = x;
                x = nextx;
            } else if (greater(nextx.key, x.key)) {
                x.sibling = nextx.sibling;
                link(nextx, x);
            } else {
                if (prevx == null) {
                    this.head = nextx;
                } else {
                    prevx.sibling = nextx;
                }
                link(x, nextx);
                x = nextx;
            }
            nextx = x.sibling;
        }
        return this;
    }

    IndexBinomialMinPQ()
    {
        comparator = null;
    }
};

#endif // INDEX_BINOMIAL_MIN_PQ_H
