private:

struct node {
    node** next;

    node()
    {
        next = new node* [R];
        for (int i = 0; i < R; i++) { next[i] = 0; }
    }
};

typedef node* link;

link head;

Item searchR(link h, Key v, int d)
{
    int i = digit(v, d);
    if (h == 0) { return nullItem; }
    if (i == NULLdigit) {
        Item dummy(v);
        return dummy;
    }
    return searchR(h->next[i], v, d + 1);
}

void insertR(link& h, Item x, int d)
{
    int i = digit(x.key(), d);
    if (h == 0) { h = new node; }
    if (i == NULLdigit) { return; }
    insertR(h->next[i], x, d + 1);
}

public:

ST(int maxN) { head = 0; }

Item search(Key v) { return searchR(head, v, 0); }

void insert(Item x) { insertR(head, x, 0); }

