private:

void insertR(link& h, Item x)
{
    if (h == 0) {
        h = new node(x);
        return;
    }
    if (rand() < RAND_MAX / (h->N + 1)) {
        insertT(h, x);
        return;
    }
    if (x.key() < h->item.key()) {
        insertR(h->l, x);
    } else { insertR(h->r, x); }
    h->N++;
}

public:

void insert(Item x) { insertR(head, x); }

