#include <iostream>

using std::cin;
using std::cout;

struct node {
    int v;
    node* next;

    node(int x, node* t)
    {
        v = x;
        next = t;
    }
};

typedef node* link;

int main()
{
    int i, j;
    link adj[V];
    for (i = 0; i < V; i++) { adj[i] = 0; }
    while (cin >> i >> j) {
        adj[j] = new node(i, adj[j]);
        adj[i] = new node(j, adj[i]);
    }
}

