#ifndef INDEX_FIBONACCI_MIN_PQ_H
#define INDEX_FIBONACCI_MIN_PQ_H

class Index_fibonacci_min_pq {

};

#include <memory>

template<typename Key>
class Index_fibonacci_min_pq_node;

template<typename Key>
class Index_fibonacci_min_pq_iterator;

template<typename Key>
class Index_fibonacci_min_pq_reverse_iterator;

template<typename T>
struct Index_fibonacci_min_pq_key_comparator;

template<typename Key, typename Comparator = Index_fibonacci_min_pq_key_comparator<Key>>
class Index_fibonacci_min_pq;

template<typename Key>
struct Index_fibonacci_min_pq_node_pointer_traits {
    using Key_type = Key;

    using Node_type = Index_fibonacci_min_pq_node<Key_type>;
    using Node_raw_pointer = Index_fibonacci_min_pq_node<Key_type>*;
    using Node_owning_pointer = std::unique_ptr<Node_type>;
    using Node_shared_pointer = std::shared_ptr<Node_type>;
    using Shared_key_pointer = std::shared_ptr<Key_type>;
    using Size_type = std::size_t;
};

template<typename Key>
class Index_fibonacci_min_pq_node {
public:
    using Node_traits = Index_fibonacci_min_pq_node_pointer_traits<Key>;
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
    bool mark;
    Node_owning_pointer prev;
    Node_owning_pointer next;
    Node_owning_pointer parent;
    Node_owning_pointer child;

    template<typename, typename, typename>
    friend class Index_fibonacci_min_pq;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_reverse_iterator;
};

template<typename Key, typename Value>
class Index_fibonacci_min_pq_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using Node_traits = Index_fibonacci_min_pq_node_pointer_traits<Key, Value>;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Node_raw_pointer = typename Node_traits::Node_raw_pointer;
    using Tree_type = Index_fibonacci_min_pq<Key_type, Value_type>;
    using Tree_pointer = Tree_type*;

    using Reference_type = Value_type&;

    Index_fibonacci_min_pq_iterator() noexcept = delete;

    explicit Index_fibonacci_min_pq_iterator(Tree_pointer tree) noexcept : _index{0}, _tree{tree}
    {
        _construct_in_order(_tree->_get_root());
    }

    Index_fibonacci_min_pq_iterator(Tree_pointer tree, int index) noexcept : _index{index}, _tree{tree}
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

    inline Index_fibonacci_min_pq_iterator& operator++()
    {
        ++_index;
        if (_index >= _in_order.size()) {
            _index = -1;
        }
        return *this;
    }

    inline Index_fibonacci_min_pq_iterator operator++(int)
    {
        Index_fibonacci_min_pq_iterator t{*this};
        ++(*this);
        return t;
    }

    inline Index_fibonacci_min_pq_iterator& operator--()
    {
        if (_index > 0) {
            --_index;
        }
        return *this;
    }

    inline Index_fibonacci_min_pq_iterator operator--(int)
    {
        Index_fibonacci_min_pq_iterator t{*this};
        --(*this);
        return t;
    }

    Node_raw_pointer operator[](const int& index)
    {
        return _in_order[index];
    }

    friend
    inline bool operator==(const Index_fibonacci_min_pq_iterator& x, const Index_fibonacci_min_pq_iterator& y)
    {
        return x._in_order == y._in_order && x._index == y._index;
    }

    friend
    inline bool operator!=(const Index_fibonacci_min_pq_iterator& x, const Index_fibonacci_min_pq_iterator& y) { return !(x == y); }

private:
    template<typename>
    friend class Index_fibonacci_min_pq;
};

template<typename T>
struct Index_fibonacci_min_pq_key_comparator {
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
class Index_fibonacci_min_pq {
public:
    using Node_traits = Index_fibonacci_min_pq_node_pointer_traits<Key>;
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
    using Iterator_type = Index_fibonacci_min_pq_iterator<Key_type, Value_type>;
    using Reverse_iterator_type = Index_fibonacci_min_pq_reverse_iterator<Key_type, Value_type>;

    Iterator_type begin() { return Iterator_type(this, 0); }

    Iterator_type end() { return Iterator_type(this, -1); }

    Index_fibonacci_min_pq(int N)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Cannot create a priority queue of negative size"); }
        n = N;
        nodes = (Node<Key>[])
        new Node[n];
        comp = new MyComparator();
    }

    Index_fibonacci_min_pq(Comparator<Key> C, int N)
    {
        if (N < 0) { throw utility::Illegal_argument_exception("Cannot create a priority queue of negative size"); }
        n = N;
        nodes = (Node<Key>[])
        new Node[n];
        comp = C;
    }

    bool is_empty()
    {
        return size == 0;
    }

    bool contains(int i)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        else { return nodes[i] != null; }
    }

    int size()
    {
        return size;
    }

    void insert(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (contains(i)) { throw utility::Illegal_argument_exception("Specified index is already in the queue"); }
        Node <Key> x = new Node<Key>();
        x.key = key;
        x.index = i;
        nodes[i] = x;
        ++size;
        head = insert(x, head);
        if (min == null) { min = head; }
        else { min = (greater(min.key, key)) ? head : min; }
    }

    int minIndex()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        return min.index;
    }

    Key minKey()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        return min.key;
    }

    int delMin()
    {
        if (is_empty()) { throw new NoSuchElementException("Priority queue is empty"); }
        head = cut(min, head);
        Node <Key> x = min.child;
        int index = min.index;
        min.key = null;                    //For garbage collection
        if (x != null) {
            do {
                x.parent = null;
                x = x.next;
            } while (x != min.child);
            head = meld(head, x);
            min.child = null;            //For garbage collection
        }
        size--;
        if (!is_empty()) { consolidate(); }
        else { min = null; }
        nodes[index] = null;
        return index;
    }

    Key keyOf(int i)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not in the queue"); }
        return nodes[i].key;
    }

    void changeKey(int i, Key key)
    {
        if (i < 0 || i >= n) { throw new IndexOutOfBoundsException(); }
        if (!contains(i)) { throw new NoSuchElementException("Specified index is not in the queue"); }
        if (greater(key, nodes[i].key)) { increaseKey(i, key); }
        else { decreaseKey(i, key); }
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
        if (greater(min.key, key)) { min = x; }
        if (x.parent != null && greater(x.parent.key, key)) {
            cut(i);
        }
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
        Node <Key> x = nodes[i];
        x.key = null;                //For garbage collection
        if (x.parent != null) {
            cut(i);
        }
        head = cut(x, head);
        if (x.child != null) {
            Node <Key> child = x.child;
            x.child = null;            //For garbage collection
            x = child;
            do {
                child.parent = null;
                child = child.next;
            } while (child != x);
            head = meld(head, child);
        }
        if (!is_empty()) { consolidate(); }
        else { min = null; }
        nodes[i] = null;
        size--;
    }

private:
    Node_owning_pointer head;
    std::vector<Raw_node_pointer> nodes;
    int n;
    Comparator_type comp;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_iterator;

    template<typename, typename>
    friend class Index_fibonacci_min_pq_reverse_iterator;

    bool greater(Key n, Key m)
    {
        if (n == null) { return false; }
        if (m == null) { return true; }
        return comp.compare(n, m) > 0;
    }

    void link(Node <Key> root1, Node <Key> root2)
    {
        root1.parent = root2;
        root2.child = insert(root1, root2.child);
        root2.order++;
    }

    void cut(int i)
    {
        Node <Key> x = nodes[i];
        Node <Key> parent = x.parent;
        parent.child = cut(x, parent.child);
        x.parent = null;
        parent.order--;
        head = insert(x, head);
        parent.mark = !parent.mark;
        if (!parent.mark && parent.parent != null) {
            cut(parent.index);
        }
    }

    void consolidate()
    {
        table.clear();
        Node <Key> x = head;
        int maxOrder = 0;
        min = head;
        Node <Key> y = null, z = null;
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
            if (y.order > maxOrder) { maxOrder = y.order; }
        } while (x != head);
        head = null;
        for (Node <Key> n : table.values()) {
            min = greater(min.key, n.key) ? n : min;
            head = insert(n, head);
        }
    }

    Node <Key> insert(Node <Key> x, Node <Key> head)
    {
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

    Node <Key> cut(Node <Key> x, Node <Key> head)
    {
        if (x.next == x) {
            x.next = null;
            x.prev = null;
            return null;
        } else {
            x.next.prev = x.prev;
            x.prev.next = x.next;
            Node <Key> res = x.next;
            x.next = null;
            x.prev = null;
            if (head == x) { return res; }
            else { return head; }
        }
    }

    Node <Key> meld(Node <Key> x, Node <Key> y)
    {
        if (x == null) { return y; }
        if (y == null) { return x; }
        x.prev.next = y.next;
        y.next.prev = x.prev;
        x.prev = y;
        y.next = x;
        return x;
    }

};

#endif // INDEX_FIBONACCI_MIN_PQ_H
