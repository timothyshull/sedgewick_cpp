#ifndef CH_4_4_STACK_ADT_IMPLEMENTATIONS_LINKED_LIST_STACK_H
#define CH_4_4_STACK_ADT_IMPLEMENTATIONS_LINKED_LIST_STACK_H

template <class Item>
class STACK
{
private:
    struct node
    { Item item; node* next;
        node(Item x, node* t)
        { item = x; next = t; }
    };
    typedef node *link;
    link head;
public:
    STACK(int)
    { head = 0; }
    int empty() const
    { return head == 0; }
    void push(Item x)
    { head = new node(x, head); }
    Item pop()
    { Item v = head->item; link t = head->next;
        delete head; head = t; return v; }
};

#endif //CH_4_4_STACK_ADT_IMPLEMENTATIONS_LINKED_LIST_STACK_H
