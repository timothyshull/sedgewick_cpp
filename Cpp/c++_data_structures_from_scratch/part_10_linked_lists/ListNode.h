#ifndef PART_10_LINKED_LISTS_LISTNODE_H
#define PART_10_LINKED_LISTS_LISTNODE_H

namespace dss {
    template<class T>
    struct ListNode {
        ListNode(const T &sourceElement);

        T element;

        ListNode *left;
        ListNode *right;
    };

    template<class T>
    inline ListNode<T>::ListNode(const T &sourceElement):
            element(sourceElement),
            left(nullptr),
            right(nullptr) {
        // ...
    }
};


#endif //PART_10_LINKED_LISTS_LISTNODE_H
