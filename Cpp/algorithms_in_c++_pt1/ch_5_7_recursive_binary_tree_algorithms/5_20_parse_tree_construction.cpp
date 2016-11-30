char *a;
int i;

struct node {
    Item item;
    node *l, *r;

    node(Item x) {
        item = x;
        l = 0;
        r = 0;
    }
};

typedef node *link;

link parse() {
    char t = a[i++];
    link x = new node(t);
    if ((t == '+') || (t == '*')) {
        x->l = parse();
        x->r = parse();
    }
    return x;
}