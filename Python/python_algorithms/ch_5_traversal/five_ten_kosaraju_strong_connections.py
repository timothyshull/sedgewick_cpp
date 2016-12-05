def tr(g):
    g_t = {}
    for u in g:
        g_t[u] = set()
    for u in g:
        for v in g[u]:
            g_t[v].add(u)
    return g_t


def scc(g):
    g_t = tr(g)
    sccs = list()
    seen = set()
    for u in dfs_topsort(g):
        if u in seen:
            continue
        c = walk(g_t, u, seen)
        seen.update(c)
        sccs.append(c)
    return sccs
