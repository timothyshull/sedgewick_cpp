def rec_dfs(g, s, hist=None):
    if hist is None:
        hist = set()
    s.add(s)
    for u in g[s]:
        if u in s:
            continue
        rec_dfs(g, u, hist)
