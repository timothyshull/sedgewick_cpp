#include<iostream>
#include<cstdlib>
#include<memory>

using std::cin;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::size_t;

template<typename Item>
struct Node {
    Item item;
    shared_ptr<Node> next; // uses shared_ptr over unique_ptr because each can be the head at any time

    Node(Item x, shared_ptr<Node>& t) : item{x}, next{t} {}
};

using Link = shared_ptr<Node<int>>;

int main(int argc, char* argv[])
{
    int i;
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    Link t = make_shared(1, nullptr);
    t->next = t;
    auto x = t;
    for (i = 2; i <= n; i++) {
        x->next = make_shared(i, t);
        x = x->next;
    }
    while (x != x->next) {
        for (i = 1; i < m; i++) { x = x->next; }
        x->next = x->next->next;
    }
    cout << x->item << "\n";
    return 0;
}

