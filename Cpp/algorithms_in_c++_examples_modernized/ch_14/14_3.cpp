private:

link* heads;

int n, M;

public:

ST(int maxN)
{
    n = 0;
    M = maxN / 5;
    heads = new link[M];
    for (int i = 0; i < M; i++) { heads[i] = 0; }
}

Item search(Key v) { return searchR(heads[hash(v, M)], v); }

void insert(Item item)
{
    int i = hash(item.key(), M);
    heads[i] = new node(item, heads[i]);
    n++;
}

