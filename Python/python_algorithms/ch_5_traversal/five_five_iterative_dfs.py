def iter_dfs(g, s):
    hist = set()
    q = list()
    q.append(s)
    while q:
        u = q.pop()
        if u in hist:
            continue
        hist.add(u)
        q.extend(g[u])
        yield u
