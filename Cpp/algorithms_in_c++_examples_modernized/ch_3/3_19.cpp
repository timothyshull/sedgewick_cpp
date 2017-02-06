#include <iostream>
#include <vector>
#include <memory>

using std::cin;
using std::cout;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::size_t;

template<typename Item>
struct Node {
    Item v;
    shared_ptr<Node<Item>> next;

    Node(Item x, Node* t) : v{x}, next{t} {}
};

using Link = shared_ptr<Node<int>>;

int main(int argc, char* argv[])
{
    int i;
    int j;
    size_t v = static_cast<size_t>(atoi(argv[1]));
    vector<Link> adj{v, nullptr};
    while (cin >> i >> j) {
        adj[j] = make_shared(i, adj[j]);
        adj[i] = make_shared(j, adj[i]);
    }
    return 0;
}

