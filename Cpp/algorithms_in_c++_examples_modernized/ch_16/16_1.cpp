template<class Item, class Key>
struct entry { Key key; Item item; struct node* next; };

struct node {
    int m;
    entry<Item, Key> b[M];

    node() { m = 0; }
};

typedef node* link;

