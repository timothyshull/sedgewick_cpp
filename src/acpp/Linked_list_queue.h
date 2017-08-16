// Program 4.14 - FIFO queue linked-list implementation
#ifndef LINKED_LIST_QUEUE_H
#define LINKED_LIST_QUEUE_H

template<typename Item_t>
struct Queue_node;

template<typename Item_t>
struct Queue_node {
    using Raw_node_pointer = Queue_node<Item_t>*;
    Item_t item;
    Raw_node_pointer next;

    Queue_node(Item_t& x) : item{x}, next{nullptr} {}

    Queue_node() = default;

    ~Queue_node() = default;
};

template<typename Item_t>
class Queue {
public:
    using Raw_node_pointer = Queue_node<Item_t>*;
    using Owning_node_pointer = Queue_node<Item_t>*;

    Queue() : _head{nullptr} {}

    ~Queue()
    {
        Raw_node_pointer n{_head};
        while (n != nullptr) {
            Raw_node_pointer t{n->next};
            delete n;
            n = t;
        }
    }

    bool empty() const { return _head == nullptr; }

    void put(Item_t& x)
    {
        Raw_node_pointer t{_tail};
        _tail = new Queue_node<Item_t>{x};
        if (_head == nullptr) {
            _head = _tail;
        } else { t->next = _tail; }
    }

    void put(Item_t&& x)
    {
        Raw_node_pointer t{_tail};
        _tail = new Queue_node<Item_t>{x};
        if (_head == nullptr) {
            _head = _tail;
        } else { t->next = _tail; }
    }

    Item_t get()
    {
        Item_t v = _head->item;
        Raw_node_pointer t = _head->next;
        delete _head;
        _head = t;
        return v;
    }

private:
    Owning_node_pointer _head;
    Raw_node_pointer _tail;
};

#endif // LINKED_LIST_QUEUE_H
