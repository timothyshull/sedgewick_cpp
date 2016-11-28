#ifndef PART_10_LINKED_LISTS_LIST_H
#define PART_10_LINKED_LISTS_LIST_H

#include "Allocator.h"
#include "ConstIter.h"
#include "ListIter.h"
#include "ListNode.h"
#include "ReverseIter.h"

namespace dss {
    template<class T>
    class List {
    public:
        friend class ListIter<List>;

        typedef ConstIter<List> const_iterator;
        typedef ReverseIter<const_iterator> const_reverse_iterator;
        typedef const T *const_pointer;
        typedef const T &const_reference;
        typedef ListIter<List> iterator;
        typedef ReverseIter<iterator> reverse_iterator;
        typedef T *pointer;
        typedef T &reference;
        typedef int difference_type;
        typedef unsigned int size_type;
        typedef T value_type;

        List();

        List(const List &source);

        ~List();

        bool empty() const;

        size_type size() const;

        const_iterator begin() const;

        const_iterator end() const;

        const_reverse_iterator rbegin() const;

        const_reverse_iterator rend() const;

        const_reference front() const;

        const_reference back() const;

        iterator begin();

        iterator end();

        reverse_iterator rbegin();

        reverse_iterator rend();

        reference front();

        reference back();

        List &operator=(const List &rhs);

        iterator insert(const_iterator insertionPoint, const T &source);

        iterator erase(const_iterator erasurePoint);

        void push_front(const T &source);

        void push_back(const T &source);

        void pop_front();

        void pop_back();

        void clear();

    private:
        typedef ListNode<T> Node;

        Node *_createNode(const T &source);

        void _destroyNode(Node *n);

        void _destroyAllNodes();

        Node *_head;
        Node *_tail;
        size_type _size;
        Allocator<Node> _alloc;
    };

    template<class T>
    inline List<T>::List():
            _head(nullptr),
            _tail(nullptr),
            _size(0) {
        // ...
    }

    template<class T>
    inline List<T>::~List() {
        _destroyAllNodes();
    }

    template<class T>
    inline bool List<T>::empty() const {
        return _size == 0;
    }

    template<class T>
    inline typename List<T>::size_type List<T>::size() const {
        return _size;
    }

    template<class T>
    inline typename List<T>::const_reference List<T>::front() const {
        return _head->element;
    }

    template<class T>
    inline typename List<T>::const_reference List<T>::back() const {
        return _tail->element;
    }

    template<class T>
    inline typename List<T>::reference List<T>::front() {
        return _head->element;
    }

    template<class T>
    inline typename List<T>::reference List<T>::back() {
        return _tail->element;
    }

    template<class T>
    void List<T>::push_front(const T &source) {
        Node *newNode = _createNode(source);

        if (empty()) {
            _head = newNode;
            _tail = newNode;
        } else {
            newNode->right = _head;

            _head->left = newNode;
            _head = newNode;
        }

        ++_size;
    }

    template<class T>
    void List<T>::push_back(const T &source) {
        Node *newNode = _createNode(source);

        if (empty()) {
            _head = newNode;
            _tail = newNode;
        } else {
            newNode->left = _tail;

            _tail->right = newNode;
            _tail = newNode;
        }

        ++_size;
    }

    template<class T>
    typename List<T>::Node *List<T>::_createNode(const T &source) {
        Node *newNode = _alloc.allocate(1);
        _alloc.construct(newNode, Node(source));

        return newNode;
    }

    template<class T>
    inline void List<T>::_destroyNode(Node *n) {
        _alloc.destroy(n);
        _alloc.deallocate(n);
    }

    template<class T>
    void List<T>::_destroyAllNodes() {
        Node *n = _head;
        Node *next;

        while (n != nullptr) {
            next = n->right;
            _destroyNode(n);
            n = next;
        }
    }

    template<class T>
    void List<T>::pop_front() {
        Node *newHead = _head->right;

        if (newHead != nullptr)
            newHead->left = nullptr;
        else
            _tail = nullptr;

        _destroyNode(_head);
        _head = newHead;
        --_size;
    }

    template<class T>
    void List<T>::pop_back() {
        Node *newTail = _tail->left;

        if (newTail != nullptr)
            newTail->right = nullptr;
        else
            _head = nullptr;

        _destroyNode(_tail);
        _tail = newTail;
        --_size;
    }

    template<class T>
    void List<T>::clear() {
        _destroyAllNodes();

        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    template<class T>
    inline typename List<T>::iterator List<T>::begin() {
        return iterator(this, _head);
    }

    template<class T>
    inline typename List<T>::iterator List<T>::end() {
        return iterator(this, nullptr);
    }

    template<class T>
    inline typename List<T>::const_iterator List<T>::begin() const {
        return const_cast<List *>(this)->begin();
    }

    template<class T>
    inline typename List<T>::const_iterator List<T>::end() const {
        return const_cast<List *>(this)->end();
    }

    template<class T>
    List<T>::List(const List &source):
            _head(nullptr),
            _tail(nullptr),
            _size(0) {
        for (const_iterator i = source.begin(); i != source.end(); ++i)
            push_back(*i);
    }

    template<class T>
    List<T> &List<T>::operator=(const List &rhs) {
        if (size() >= rhs.size()) {
            while (size() != rhs.size())
                pop_back();

            iterator e = begin();
            const_iterator c = rhs.begin();

            while (e != end())
                *e++ = *c++;
        } else {
            iterator e = begin();
            const_iterator c = rhs.begin();

            while (e != end())
                *e++ = *c++;

            while (c != rhs.end())
                push_back(*c++);
        }

        return *this;
    }

    template<class T>
    typename List<T>::iterator List<T>::insert(const_iterator insertionPoint,
                                               const T &source) {
        if (insertionPoint == begin()) {
            push_front(source);

            return iterator(this, _head);
        } else if (insertionPoint == end()) {
            push_back(source);

            return iterator(this, _tail);
        } else {
            Node *newNode = _createNode(source);

            Node *leftNeighbor = insertionPoint._i._node->left;
            Node *rightNeighbor = insertionPoint._i._node;

            newNode->left = leftNeighbor;
            newNode->right = rightNeighbor;

            leftNeighbor->right = newNode;
            rightNeighbor->left = newNode;

            ++_size;

            return iterator(this, newNode);
        }
    }

    template<class T>
    typename List<T>::iterator List<T>::erase(const_iterator erasurePoint) {
        if (erasurePoint == begin()) {
            pop_front();

            return iterator(this, _head);
        } else if (erasurePoint._i._node == _tail) {
            pop_back();

            return end();
        } else {
            Node *trash = erasurePoint._i._node;
            Node *leftNeighbor = trash->left;
            Node *rightNeighbor = trash->right;

            _destroyNode(trash);
            --_size;

            leftNeighbor->right = rightNeighbor;
            rightNeighbor->left = leftNeighbor;

            return iterator(this, rightNeighbor);
        }
    }

    template<class T>
    inline typename List<T>::const_reverse_iterator List<T>::rbegin() const {
        return const_reverse_iterator(end());
    }

    template<class T>
    inline typename List<T>::const_reverse_iterator List<T>::rend() const {
        return const_reverse_iterator(begin());
    }

    template<class T>
    inline typename List<T>::reverse_iterator List<T>::rbegin() {
        return reverse_iterator(end());
    }

    template<class T>
    inline typename List<T>::reverse_iterator List<T>::rend() {
        return reverse_iterator(begin());
    }
};

#endif //PART_10_LINKED_LISTS_LIST_H
