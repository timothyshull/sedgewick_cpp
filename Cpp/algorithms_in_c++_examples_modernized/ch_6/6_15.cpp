struct node {
    Item item;
    node* next;

    node(Item x)
    {
        item = x;
        next = 0;
    }
};

typedef node* link;

link randlist(int);

link scanlist(int&);

void showlist(link);

link sortlist(link);

