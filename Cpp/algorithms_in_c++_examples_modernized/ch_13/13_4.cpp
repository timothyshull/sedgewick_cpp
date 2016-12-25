link joinLR(link a, link b)
{
    if (a == 0) { return b; }
    if (b == 0) { return a; }
    if (rand() / (RAND_MAX / (a->N + b->N) + 1) < a->N) {
        a->r = joinLR(a->r, b);
        return a;
    } else {
        b->l = joinLR(a, b->l);
        return b;
    }
}

