#ifndef COLLECTED_TREE_TO_DAG_H
#define COLLECTED_TREE_TO_DAG_H

int compressR(link h)
{
    STx st;
    if (h == NULL) { return 0; }
    l = compressR(h->l);
    r = compressR(h->r);
    t = st.index(l, r);
    adj[t].l = l;
    adj[t].r = r;
    return t;
}

#endif // COLLECTED_TREE_TO_DAG_H
