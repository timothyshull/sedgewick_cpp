#ifndef FIBONACCI_MIN_PQ_H
#define FIBONACCI_MIN_PQ_H

#include <memory>

template<typename Key>
class Fibonacci_min_pq_node;

template<typename Key>
class Fibonacci_min_pq_iterator;

template<typename Key>
class Fibonacci_min_pq_reverse_iterator;

template<typename T>
struct Fibonacci_min_pq_key_comparator;

template<typename Key, typename Comparator = Fibonacci_min_pq_key_comparator<Key>>
class Fibonacci_min_pq;

template<typename Key>
struct Fibonacci_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Fibonacci_min_pq_node<Key_type>;
    using Node_raw_pointer = Fibonacci_min_pq_node<Key_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key>
class Fibonacci_min_pq_node {
public:
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key>;
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

    Node_owning_pointer prev;
    Node_owning_pointer next;
    Node_owning_pointer _child;

    template<typename, typename, typename>
    friend class Fibonacci_min_pq;

    template<typename, typename>
    friend class Fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Fibonacci_min_pq_reverse_iterator;
};

template<typename Key, typename Value>
class Fibonacci_min_pq_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Fibonacci_min_pq<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Fibonacci_min_pq_iterator() noexcept = delete;

    explicit Fibonacci_min_pq_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Fibonacci_min_pq_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
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

    inline Fibonacci_min_pq_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Fibonacci_min_pq_iterator operator++(int)
    {
        Fibonacci_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Fibonacci_min_pq_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Fibonacci_min_pq_iterator operator--(int)
    {
        Fibonacci_min_pq_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Fibonacci_min_pq_iterator& x, const Fibonacci_min_pq_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Fibonacci_min_pq_iterator& x, const Fibonacci_min_pq_iterator& y) { return !(x == y); }

private:
    template<typename>
    friend class Fibonacci_min_pq;
};

template<typename T>
struct Fibonacci_min_pq_key_comparator {
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
class Fibonacci_min_pq {
public:
    using Node_traits = Fibonacci_min_pq_node_pointer_traits<Key>;
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
    using Iterator_type = Fibonacci_min_pq_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Fibonacci_min_pq_reverse_iterator<Key_type, Value_type>;

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

Fibonacci_min_pq(Comparator<Key> C) {
        comp = C;
    }

Fibonacci_min_pq() {
        comp = new MyComparator();
    }

Fibonacci_min_pq(Key[] a) {
        comp = new MyComparator();
        for (Key k : a) insert(k);
    }

Fibonacci_min_pq(Comparator<Key> C, Key[] a) {
        comp = C;
        for (Key k : a) insert(k);
    }
 bool is_empty() {
        return size == 0;
    }

int size() {
        return size;
    }

    void insert(Key key) {
        Node x = new Node();
        x.key = key;
        size++;
        head = insert(x, head);
        if (min == null) min = head;
        else min = (greater(min.key, key)) ? head : min;
    }

Key minKey() {
        if (is_empty()) throw new NoSuchElementException("Priority queue is empty");
        return min.key;
    }

Key delMin() {
        if (is_empty()) throw new NoSuchElementException("Priority queue is empty");
        head = cut(min, head);
        Node x = min.child;
        Key key = min.key;
        min.key = null;
        if (x != null) {
            head = meld(head, x);
            min.child = null;
        }
        size--;
        if (!is_empty()) consolidate();
        else min = null;
        return key;
    }

 FibonacciMinPQ<Key> create_union(FibonacciMinPQ<Key> that) {
        this.head = meld(head, that.head);
        this.min = (greater(this.min.key, that.min.key)) ? that.min : this.min;
        this.size = this.size + that.size;
        return this;
    }
private:
    Node_owning_pointer head;
    Node_owning_pointer min;
    int size;
    std::map<int, Raw_node_pointer> table;
    Comparator_type comp;

    template<typename, typename>
    friend class Fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Fibonacci_min_pq_reverse_iterator;
 bool greater(Key n, Key m) {
        if (n == null) return false;
        if (m == null) return true;
        return comp.compare(n, m) > 0;
    }

void link(Node root1, Node root2) {
        root2.child = insert(root1, root2.child);
        root2.order++;
    }

void consolidate() {
        table.clear();
        Node x = head;
        int maxOrder = 0;
        min = head;
        Node y = null;
        Node z = null;
        do {
            y = x;
            x = x.next;
            z = table.get(y.order);
            while (z != null) {
                table.remove(y.order);
                if (greater(y.key, z.key)) {
                    link(y, z);
                    y = z;
                } else {
                    link(z, y);
                }
                z = table.get(y.order);
            }
            table.put(y.order, y);
            if (y.order > maxOrder) maxOrder = y.order;
        } while (x != head);
        head = null;
        for (Node n : table.values()) {
            if (n != null) {
                min = greater(min.key, n.key) ? n : min;
                head = insert(n, head);
            }
        }
    }

Node insert(Node x, Node head) {
        if (head == null) {
            x.prev = x;
            x.next = x;
        } else {
            head.prev.next = x;
            x.next = head;
            x.prev = head.prev;
            head.prev = x;
        }
        return x;
    }

Node cut(Node x, Node head) {
        if (x.next == x) {
            x.next = null;
            x.prev = null;
            return null;
        } else {
            x.next.prev = x.prev;
            x.prev.next = x.next;
            Node res = x.next;
            x.next = null;
            x.prev = null;
            if (head == x) return res;
            else return head;
        }
    }

Node meld(Node x, Node y) {
        if (x == null) return y;
        if (y == null) return x;
        x.prev.next = y.next;
        y.next.prev = x.prev;
        x.prev = y;
        y.next = x;
        return x;
    }
};

#endif // FIBONACCI_MIN_PQ_H
