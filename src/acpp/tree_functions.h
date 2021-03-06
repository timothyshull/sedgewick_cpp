// Program 5.14 - Recursive tree traversal
// Program 5.15 - Preorder traversal (nonrecursive) **
// Program 5.16 - Level-order traversal **
// Program 5.17 - Computation of tree parameters
// Program 5.18 - Quick tree-print function // inorder traversal **
// Program 5.19 - Construction of a tournament
// Program 5.20 - Construction of a parse tree
// Program 5.21 - Depth-first search
// Program 5.22 - Breadth-first search
#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

#include <queue>
#include <stack>
#include <iostream>

template<typename Item_t>
struct Tree_node;

template<typename Item_t>
struct Tree_node {
    Item_t item;
    Tree_node<Item_t>* left;
    Tree_node<Item_t>* right;
};

template<typename Item_t, typename Visitor_type>
void preorder_recursive(Tree_node<Item_t>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }
    visit(root);
    preorder_recursive<Item_t, Visitor_type>(root->left, visit);
    preorder_recursive<Item_t, Visitor_type>(root->right, visit);
}

template<typename Item_t, typename Visitor_type>
void preorder_iterative(Tree_node<Item_t>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::stack<Tree_node<Item_t>*> stack;
    Tree_node<Item_t>* tmp;

    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        visit(tmp);
        if (tmp->right != nullptr) { stack.push(tmp->right); }
        if (tmp->left != nullptr) { stack.push(tmp->left); }
    }
}

template<typename Item_t, typename Visitor_type>
void level_order(Tree_node<Item_t>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::queue<Tree_node<Item_t>*> queue;
    Tree_node<Item_t>* tmp;

    queue.push(root);
    while (!queue.empty()) {
        tmp = queue.front();
        queue.pop();
        visit(tmp);
        if (tmp->left != nullptr) { queue.push(tmp->left); }
        if (tmp->right != nullptr) { queue.push(tmp->right); }
    }
}

template<typename Item_t>
int count(Tree_node<Item_t>* root)
{
    if (root == nullptr) { return 0; }
    return count(root->left) + count(root->right) + 1;
}

template<typename Item_t>
int height(Tree_node<Item_t>* root)
{
    if (root == nullptr) { return -1; }
    auto u = height(root->left);
    auto v = height(root->right);
    if (u > v) { return u + 1; } else { return v + 1; }
}

template<typename Item_t>
void print_node(Item_t x, int h)
{
    for (int i = 0; i < h; i++) { std::cout << "  "; }
    std::cout << x << "\n";
}

template<typename Item_t>
void show(Tree_node<Item_t>* node, int h)
{
    if (node == nullptr) {
        print_node('*', h);
        return;
    }
    show(node->right, h + 1);
    print_node(node->item, h);
    show(node->left, h + 1);
}

// TODO: sort these out
template<typename Item_t>
Tree_node<Item_t>* max(std::vector<Item_t>& a, int l, int r)
{
    auto m = (l + r) / 2;
    Tree_node<Item_t>* x{new Tree_node<Item_t>{a[m]}};
    if (l == r) { return x; }
    x->left = max(a, l, m);
    x->right = max(a, m + 1, r);
    Item_t u = x->left->item;
    Item_t v = x->right->item;
    if (u > v) {
        x->item = u;
    } else { x->item = v; }
    return x;
}

template<typename Item_t>
Tree_node<Item_t>* parse()
{
    char t = a[i++];
    Tree_node<Item_t>* x{new Tree_node<Item_t>{t}};
    if ((t == '+') || (t == '*')) {
        x->left = parse();
        x->right = parse();
    }
    return x;
}

template<typename Item_t, typename Visitor_type>
void depth_first_traverse(int k, Visitor_type& visit)
{
    visit(k);
    visited[k] = 1;
    for (link t = adj[k]; t != 0; t = t->next) {
        if (!visited[t->v]) { depth_first_traverse(t->v, visit); }
    }
}

template<typename Item_t, typename Visitor_type>
void breadth_first_traverse(int k, Visitor_type& visit)
{
    std::queue<int> q(V * V);
    q.push(k);
    while (!q.empty()) {
        if (visited[k = q.get()] == 0) {
            visit(k);
            visited[k] = 1;
            for (link t = adj[k]; t != 0; t = t->next) {
                if (visited[t->v] == 0) { q.put(t->v); }
            }
        }
    }
}

#endif // TREE_FUNCTIONS_H
