#ifndef PART_10_LINKED_LISTS_LIST_ITER_H
#define PART_10_LINKED_LISTS_LIST_ITER_H

#include <iterator>

namespace dss {
    template<class List>
    class ListIter {
    public:
        friend class List;

        typedef typename List::pointer pointer;
        typedef typename List::reference reference;
        typedef typename List::difference_type difference_type;
        typedef typename List::value_type value_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        ListIter();

        bool operator==(const ListIter &rhs) const;

        bool operator!=(const ListIter &rhs) const;

        pointer operator->() const;

        reference operator*() const;

        ListIter &operator++();

        ListIter &operator--();

        ListIter operator++(int n);

        ListIter operator--(int n);

    private:
        typedef typename List::Node Node;

        ListIter(List *list, Node *node);

        void _pointToNextNode();

        void _pointToPreviousNode();

        List *_list;
        Node *_node;
    };

    template<class List>
    inline ListIter<List>::ListIter() {
        // ...
    }

    template<class List>
    inline bool ListIter<List>::operator==(const ListIter &rhs) const {
        return _node == rhs._node;
    }

    template<class List>
    inline bool ListIter<List>::operator!=(const ListIter &rhs) const {
        return _node != rhs._node;
    }

    template<class List>
    inline typename ListIter<List>::pointer ListIter<List>::operator->() const {
        return &_node->element;
    }

    template<class List>
    inline typename ListIter<List>::reference ListIter<List>::operator*() const {
        return _node->element;
    }

    template<class List>
    inline ListIter<List> &ListIter<List>::operator++() {
        _pointToNextNode();

        return *this;
    }

    template<class List>
    inline ListIter<List> &ListIter<List>::operator--() {
        _pointToPreviousNode();

        return *this;
    }

    template<class List>
    inline ListIter<List> ListIter<List>::operator++(int n) {
        ListIter iterToOriginalNode(*this);

        _pointToNextNode();

        return iterToOriginalNode;
    }

    template<class List>
    inline ListIter<List> ListIter<List>::operator--(int n) {
        ListIter iterToOriginalNode(*this);

        _pointToPreviousNode();

        return iterToOriginalNode;
    }

    template<class List>
    inline ListIter<List>::ListIter(List *list, Node *node):
            _list(list),
            _node(node) {
        // ...
    }

    template<class List>
    inline void ListIter<List>::_pointToNextNode() {
        _node = _node->right;
    }

    template<class List>
    void ListIter<List>::_pointToPreviousNode() {
        if (_node != nullptr)
            _node = _node->left;
        else
            _node = _list->_tail;
    }
};


#endif //PART_10_LINKED_LISTS_LIST_ITER_H
