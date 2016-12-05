def dfs_topsort(g):
    hist = set()
    res = list()

    def recurse(u):
        if u in hist:
            return
        hist.add(u)
        for v in g[u]:
            recurse(v)
        res.append(u)

    for u in g:
        recurse(u)
    res.reverse()
    return res
