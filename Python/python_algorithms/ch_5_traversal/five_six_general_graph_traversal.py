def traverse(g, s, qtype=set):
    hist = set()
    q = qtype()
    q.add(s)
    while q:
        u = q.pop()
        if u in hist:
            continue
        hist.add(u)
        for v in g[u]:
            q.add(v)
        yield u
