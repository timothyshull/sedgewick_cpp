struct node {
    Item item;
    int d;
    node* l, * m, * r;

    node(Item x, int k)
    {
        item = x;
        d = k;
        l = 0;
        m = 0;
        r = 0;
    }

    node(node* h, int k)
    {
        d = k;
        l = 0;
        m = h;
        r = 0;
    }

    int internal() { return d != NULLdigit; }
};

typedef node* link;

link heads[R];

Item nullItem;

