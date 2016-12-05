def bfs(g, s):
    p = {s: None}
    q = deque([s])
    while q:
        u = q.popleft()
        for v in g[u]:
            if v in p:
                continue
            p[v] = u
            q.append(v)
    return p
