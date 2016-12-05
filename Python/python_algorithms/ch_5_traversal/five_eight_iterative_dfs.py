def iddfs(g, s):
    yielded = set()

    def recurse(rg, rs, depth, hist=None):
        if rs not in yielded:
            yield rs
            yielded.add(rs)
        if depth == 0:
            return
        if hist is None:
            hist = set()
        hist.add(rs)
        for u in rg[rs]:
            if u in hist:
                continue
            for v in recurse(rg, u, depth - 1, hist):
                yield v

    n = len(g)
    for d in range(n):
        if len(yielded) == n:
            break
        for u in recurse(g, s, d):
            yield u
