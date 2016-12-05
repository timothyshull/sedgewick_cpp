a, b, c, d, e, f, g, h = range(8)  # generates a list of incremental integers,

N = [
    {b, c, d, e, f},  # a
    {c, e},  # b
    {d},  # c
    {e},  # d
    {f},  # e
    {c, g, h},  # f
    {f, h},  # g
    {f, g}  # h
]


# s is the start node
def walk(graph, s, hist=set()):
    p = dict()
    q = set()
    p[s] = None
    q.add(s)
    while q:
        u = q.pop()
        for v in graph[u].difference(p, hist):  # uses a set difference on the dict (as a set of its keys)
            q.add(v)
            p[v] = u
    return p
