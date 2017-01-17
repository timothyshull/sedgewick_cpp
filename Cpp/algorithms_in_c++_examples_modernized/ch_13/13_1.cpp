void balanceR(link& h)
{
    if ((h == 0) || (h->n == 1)) { return; }
    partR(h, h->n / 2);
    balanceR(h->l);
    balanceR(h->r);
}

