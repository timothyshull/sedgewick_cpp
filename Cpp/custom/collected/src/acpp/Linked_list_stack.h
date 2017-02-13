#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

template<typename Item_type>
struct Stack_node;

template<typename Item_type>
struct Stack_node {
    using Raw_node_pointer = Stack_node<Item_type>*;
    Item_type item;
    Raw_node_pointer next;

    Stack_node(Item_type& x, Raw_node_pointer t) : item{x}, next{t} {}

    Stack_node() = default;

    ~Stack_node() = default;
};

template<class Item_type>
class Stack {
public:
    using Raw_node_pointer = Stack_node<Item_type>*;
    using Owning_node_pointer = Stack_node<Item_type>*;

    Stack() : _head{nullptr} {}

    ~Stack()
    {
        Raw_node_pointer n{_head};
        while (n != nullptr) {
            Raw_node_pointer t{n->next};
            delete n;
            n = t;
        }
    }

    bool empty() const { return _head == nullptr; }

    void push(Item_type& x) { _head = new Stack_node<Item_type>{x, _head}; }

    void push(Item_type&& x) { _head = new Stack_node<Item_type>{x, _head}; }

    Item_type pop()
    {
        Item_type v = _head->item;
        Raw_node_pointer t = _head->next;
        delete _head;
        _head = t;
        return v;
    }

private:
    Owning_node_pointer _head;
};

#endif // LINKED_LIST_STACK_H
