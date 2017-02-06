#ifndef LIST_H
#define LIST_H

#include <memory>

// assumes a C style list interface

template<typename Item>
struct Node {
    Item item;
    std::shared_ptr<Node> next; // revisit shared_ptr here to avoid retain cycles

    Node(Item x, std::shared_ptr<Node> t) : item{x}, next{t} {}
};

template<typename Item>
using Link = std::shared_ptr<Node<Item>>;

template<typename Item>
void construct(int);

template<typename Item>
Node<Item> new_node(int);

template<typename Item>
void delete_node(Node<Item>);

template<typename Item>
void insert(Node<Item>, Node<Item>);

template<typename Item>
Node<Item> remove(Node<Item>);

template<typename Item>
Node<Item> next(Node<Item>);

template<typename Item>
Item item(Node<Item>);

#endif //LIST_H
