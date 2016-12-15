#include <iostream>
#include <cstdlib>

typedef int Item;

struct node {
    Item item;
    node *next;

    node(int x, node *t) : item{x}, next{t} {}

    explicit node(int x) : item{x}, next{nullptr} {}
};

static const int N = 10;

node *list_insertion_sort(node *list_head);

node *list_selection_sort(node *list_head);

node *list_bubble_sort(node *list_head);

int main() {
    node heada(0, nullptr);
    node *a = &heada;
    node *t = a;
    for (int i = 0; i < N; i++) {
        t = (t->next = new node(rand() % 1000, nullptr));
    }

//    node *new_head = list_insertion_sort(a->next);
//    node *new_head = list_selection_sort(a->next);
    node *new_head = list_bubble_sort(a->next);

    t = new_head;
    while (t != nullptr) {
        std::cout << t->item << "\n";
        t = t->next;
    }
    return 0;
}

// set t to head of list

node *list_insertion_sort(node *list_head) {
    node dummy{0, nullptr};
    node *dummy_head = &dummy;
    node *i, *j, *tmp;

    for (tmp = list_head->next; tmp != nullptr; tmp = i) {
        i = tmp->next;
        for (j = dummy_head; j->next != nullptr; j = j->next) {
            if (j->next->item > tmp->item) {
                break;
            }
        }
        tmp->next = j->next;
        j->next = tmp;
    }

    return dummy.next;
}

node *list_selection_sort(node *list_head) {
    node dummy{0, list_head};
    node *dummy_head = &dummy;
    node *out{nullptr};

    while (dummy_head->next != nullptr) {
        node *before_max = dummy_head;
        node *tmp = before_max;
        while (tmp->next != nullptr) {
            if (tmp->next->item > before_max->next->item) {
                before_max = tmp;
            }
            tmp = tmp->next;
        }
        tmp = before_max->next; // actual node containing max item
        before_max->next = tmp->next; // remove max node from input list
        tmp->next = out; // current max points to previous max
        out = tmp; // output list head is current max
    }

    return out;
}

node *list_bubble_sort(node *list_head) {
    node dummy{0, list_head};
    node *dummy_head = &dummy;
    node *i, *j, *t1, *t2;

    for (i = list_head->next; i != nullptr; i = i->next) {
        for (j = dummy_head; j->next != nullptr; j = j->next) {
            t1 = j->next;
            t2 = t1->next;
            if (t2 != nullptr && t2->item < t1->item) {
                t1->next = t2->next;
                t2->next = t1;
                j->next = t2;
            }
        }
    }

    return dummy.next;
}


// uses two lists, input list and output list, and the fact that it is easier to insert at front than back
//node *listselection(node *h) {
//    node dummy(0);
//    node *head = &dummy;
//    node *out = nullptr;
//    head->next = h;
//    while (head->next != nullptr) {
//        // has to use findmax due to single forward link
//        // actually should find the node before the node with the max element
//        node *max = findmax(head);
//        node *t = max->next;
//        max->next = t->next;
//        t->next = out;
//        out = t;
//    }
//    return out;
//}
//
//// does not conform to the requirement that only the pointers (not item) are manipulated
//node *sort(node *h) {
//    node *i;
//    node *j;
//    for (i = h; i != nullptr && i->next != nullptr; i = i->next) {
//        node *min;
//        min = i;
//        for (j = i->next; j != nullptr; j = j->next) {
//            if (j->item < min->item) {
//                min = j;
//            }
//        }
//        if (min != i) {
//            int tmp;
//            tmp = min->item;
//            min->item = i->item;
//            i->item = tmp;
//        }
//    }
//    return h;
//}

// tmp starts at index 1
// x always starts before 0
// inner loop increments upwards
// if x->next is > tmp swap tmp and x-next
// for

template<typename Comparable>
void bubble_sort(Comparable a, size_t size) {
//    int temp = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size - i; j++) {
            compexch(a, j, j - 1);
//            if (intArray[j - 1] > intArray[j]) {
//                //swap the elements!
//                temp = intArray[j - 1];
//                intArray[j - 1] = intArray[j];
//                intArray[j] = temp;
//            }
        }
    }
}

void ll_bubblesort(struct node **pp) {
    // p always points to the head of the list
    struct node *p = *pp;
    *pp = nullptr;

    while (p) {
        struct node **lhs = &p;
        struct node **rhs = &p->next;
        bool swapped = false;

        // keep going until qq holds the address of a null pointer
        while (*rhs) {
            // if the left side is greater than the right side
            if ((*rhs)->item < (*lhs)->item) {
                // swap linked node ptrs, then swap *back* their next ptrs
                std::swap(*lhs, *rhs);
                std::swap((*lhs)->next, (*rhs)->next);
                lhs = &(*lhs)->next;
                swapped = true;
            } else {   // no swap. advance both pointer-pointers
                lhs = rhs;
                rhs = &(*rhs)->next;
            }
        }

        // link last node to the sorted segment
        *rhs = *pp;

        // if we swapped, detach the final node, terminate the list, and continue.
        if (swapped) {
            // take the last node off the list and push it into the result.
            *pp = *lhs;
            *lhs = nullptr;
        } else {
            *pp = p;
            break;
        }
    }
}

template<class Item>
void exch(Item a[], size_t i, size_t j) {
    Item t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template<class Item>
void compexch(Item a[], size_t i, size_t j) { if (a[j] < a[i]) { exch(a, i, j); }}

template<class Item>
void sort(Item a[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        for (int j = i; j > l; j--) {
            compexch(a, j - 1, j);
        }
    }
}

void distcount(int a[], int l, int r) {
    int i, j, cnt[M];
    static int b[maxN];
    for (j = 0; j < M; j++) { cnt[j] = 0; }
    for (i = l; i <= r; i++) { cnt[a[i] + 1]++; }
    for (j = 1; j < M; j++) { cnt[j] += cnt[j - 1]; }
    for (i = l; i <= r; i++) { b[cnt[a[i]]++] = a[i]; }
    for (i = l; i <= r; i++) { a[i] = b[i - l]; }
}