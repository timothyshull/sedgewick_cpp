using Item = int;

struct Node {
    Node *left;
    Node *right;
    Item item;
};

struct Tree {
    Node *root;
};

bool is_leaf(Node *node) {
    return node->left == nullptr && node->right == nullptr;
}

void remove(Node* root, Item item) {
    if (root == nullptr) {
        return;
    } else if (is_leaf(root) && root->item == item) {
        delete root;
        return;
    } else {
        remove(root->right, item);
        remove(root->left, item);
    }
}