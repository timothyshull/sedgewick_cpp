// Program 6.15 - Linked-list type interface
// Program 6.16 - Linked-list selection sort
#ifndef LIST_SELECTION_SORT_H
#define LIST_SELECTION_SORT_H

struct node {
    Item item;
    node* next;

    node(Item x)
    {
        item = x;
        next = 0;
    }
};

typedef node* link;

link randlist(int);

link scanlist(int&);

void showlist(link);

link sortlist(link);

link listselection(link h)
{
    node dummy(0);
    link head = &dummy, out = 0;
    head->next = h;
    while (head->next != 0) {
        link max = findmax(head), t = max->next;
        max->next = t->next;
        t->next = out;
        out = t;
    }
    return out;
}

#endif // LIST_SELECTION_SORT_H
