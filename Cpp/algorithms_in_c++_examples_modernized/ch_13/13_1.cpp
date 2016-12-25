void balanceR(link& h)
{
    if ((h == 0) || (h->N == 1)) { return; }
    partR(h, h->N / 2);
    balanceR(h->l);
    balanceR(h->r);
}

