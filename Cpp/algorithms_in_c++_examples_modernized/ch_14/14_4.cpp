private:

Item* st;

int n, M;

Item nullItem;

public:

ST(int maxN)
{
    n = 0;
    M = 2 * maxN;
    st = new Item[M];
    for (int i = 0; i < M; i++) { st[i] = nullItem; }
}

int count() const { return n; }

void insert(Item item)
{
    int i = hash(item.key(), M);
    while (!st[i].null()) { i = (i + 1) % M; }
    st[i] = item;
    n++;
}

Item search(Key v)
{
    int i = hash(v, M);
    while (!st[i].null()) {
        if (v == st[i].key()) { return st[i]; }
        else { i = (i + 1) % M; }
    }
    return nullItem;
}

