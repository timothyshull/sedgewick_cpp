#ifndef BINOMIAL_MIN_PRIORITY_QUEUE_H
#define BINOMIAL_MIN_PRIORITY_QUEUE_H

#include <memory>

template<typename Key>
class Binomial_min_pq_node;

template<typename Key>
class Binomial_min_pq_iterator;

template<typename Key>
class Binomial_min_pq_reverse_iterator;

template<typename T>
struct Binomial_min_pq_key_comparator;

template<typename Key, typename Comparator = Binomial_min_pq_key_comparator<Key>>
class Binomial_min_pq;

template<typename Key>
struct Binomial_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Binomial_min_pq_node<Key_type>;
    using Node_raw_pointer = Binomial_min_pq_node<Key_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key>
class Binomial_min_pq_node {
public:
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key>;
    using Key_type = typename Node_traits::Key_type;
    using Node_type = typename Node_traits::Node_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Node_owning_pointer = typename Node_traits::Node_owning_pointer;
    using Node_shared_pointer = typename Node_traits::Node_shared_pointer;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = typename Node_traits::Size_type;

private:
    Shared_key_pointer _key;

    int _order;

    Node_owning_pointer _child;
    Node_owning_pointer _sibling;

    template<typename, typename, typename>
    friend class Binomial_min_pq;

    template<typename, typename>
    friend class Binomial_min_pq_iterator;

    template<typename, typename>
    friend class Binomial_min_pq_reverse_iterator;
};

template<typename Key, typename Value>
class Binomial_min_pq_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Binomial_min_pq<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Binomial_min_pq_iterator() noexcept = delete;

    explicit Binomial_min_pq_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Binomial_min_pq_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
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

    inline Binomial_min_pq_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Binomial_min_pq_iterator operator++(int)
    {
        Binomial_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Binomial_min_pq_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Binomial_min_pq_iterator operator--(int)
    {
        Binomial_min_pq_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Binomial_min_pq_iterator& x, const Binomial_min_pq_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Binomial_min_pq_iterator& x, const Binomial_min_pq_iterator& y) { return !(x == y); }

private:
    template<typename>
    friend class Binomial_min_pq;
};

template<typename T>
struct Binomial_min_pq_key_comparator {
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
class Binomial_min_pq {
public:
    using Node_traits = Binomial_min_pq_node_pointer_traits<Key>;
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
    using Difference_type = std::ptrdiff_t;  // TODO: _check on this because of the relationship with max_size
    using Iterator_type = Binomial_min_pq_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Binomial_min_pq_reverse_iterator<Key_type, Value_type>;

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

public BinomialMinPQ() {
        comp = new MyComparator();
    }

BinomialMinPQ(Comparator<Key> C) {
        comp = C;
    }

BinomialMinPQ(Key[] a) {
        comp = new MyComparator();
        for (Key k : a) insert(k);
    }

BinomialMinPQ(Comparator<Key> C, Key[] a) {
        comp = C;
        for (Key k : a) insert(k);
    } bool is_empty() {
        return head == nullptr;
    }

int size() {
        int result = 0, tmp;
        for (Node node{head}; node != null; node = node.sibling) {
            if (node.order > 30) {
                throw new ArithmeticException("The number of elements cannot be evaluated, but the priority _queue is still valid.");
            }
            tmp = 1 << node.order;
            result |= tmp;
        }
        return result;
    }

void insert(Key key) {
        Node x = new Node();
        x.key = key;
        x.order = 0;
        BinomialMinPQ<Key> H = new BinomialMinPQ<Key>(); //The Comparator oh the H heap is not used
        H.head = x;
        this.head = this.union(H).head;
    }

 Key minKey() {
        if (is_empty()) throw new NoSuchElementException("Priority _queue is empty");
        Node min = head;
        Node current = head;
        while (current.sibling != null) {
            min = (greater(min.key, current.sibling.key)) ? current : min;
            current = current.sibling;
        }
        return min.key;
    }

 Key delMin() {
        if (is_empty()) throw new NoSuchElementException("Priority _queue is empty");
        Node min = eraseMin();
        Node x = (min.child == null) ? min : min.child;
        if (min.child != null) {
            min.child = null;
            Node prevx = null, nextx = x.sibling;
            while (nextx != null) {
                x.sibling = prevx;
                prevx = x;
                x = nextx;
                nextx = nextx.sibling;
            }
            x.sibling = prevx;
            BinomialMinPQ<Key> H = new BinomialMinPQ<Key>();
            H.head = x;
            head = union(H).head;
        }
        return min.key;
    }

 BinomialMinPQ<Key> get_union(BinomialMinPQ<Key> heap) {
        if (heap == null) throw utility::Illegal_argument_exception("Cannot merge a Binomial Heap with null");
        this.head = merge(new Node(), this.head, heap.head).sibling;
        Node x = this.head;
        Node prevx = null, nextx = x.sibling;
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
private:
    Node_owning_pointer head;
    Comparator_type comp;

    template<typename, typename>
    friend class Binomial_min_pq_iterator;

    template<typename, typename>
    friend class Binomial_min_pq_reverse_iterator;

 bool greater(Key n, Key m) {
        if (n == null) return false;
        if (m == null) return true;
        return comp.compare(n, m) > 0;
    }

void link(Node root1, Node root2) {
        root1.sibling = root2.child;
        root2.child = root1;
        root2.order++;
    }

Node eraseMin() {
        Node min = head;
        Node previous = null;
        Node current = head;
        while (current.sibling != null) {
            if (greater(min.key, current.sibling.key)) {
                previous = current;
                min = current.sibling;
            }
            current = current.sibling;
        }
        previous.sibling = min.sibling;
        if (min == head) head = min.sibling;
        return min;
    }

Node merge(Node h, Node x, Node y) {
        if (x == null && y == null) return h;
        else if (x == null) h.sibling = merge(y, null, y.sibling);
        else if (y == null) h.sibling = merge(x, x.sibling, null);
        else if (x.order < y.order) h.sibling = merge(x, x.sibling, y);
        else h.sibling = merge(y, x, y.sibling);
        return h;
    }

};

#endif // BINOMIAL_MIN_PRIORITY_QUEUE_H
