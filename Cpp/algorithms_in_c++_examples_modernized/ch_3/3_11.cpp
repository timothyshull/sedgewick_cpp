#include <cstdlib>
#include <memory>
#include <random>
#include "list.h"

using std::size_t;
using std::shared_ptr;
using std::make_shared;
using std::random_device;
using std::uniform_int_distribution;
using std::default_random_engine;

void list_insertion_sort(size_t n)
{
    Node<int> head_a{0, nullptr};
    shared_ptr<Node<int>> a{&head_a};
    shared_ptr<Node<int>> t{a};
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> uniform_dist(0, 999);
    for (int i = 0; i < n; i++) {
        t->next = make_shared(uniform_dist(gen), nullptr);
        t = t->next;
    }
    Node<int> head_b(0, nullptr);
    shared_ptr<Node<int>> u;
    shared_ptr<Node<int>> x;
    shared_ptr<Node<int>> b{&head_b};
    for (t = a->next; t != 0; t = u) {
        u = t->next;
        for (x = b; x->next != 0; x = x->next) {
            if (x->next->item > t->item) { break; }
        }
        t->next = x->next;
        x->next = t;
    }
}