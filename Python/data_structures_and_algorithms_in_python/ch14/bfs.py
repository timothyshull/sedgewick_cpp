def bfs(g, s, discovered):
    level = [s]  # first level includes only s
    while len(level) > 0:
        next_level = []  # prepare to gather newly found vertices
        for u in level:
            for e in g.incident_edges(u):  # for every outgoing edge from u
                v = e.opposite(u)
                if v not in discovered:  # v is an unvisited vertex
                    discovered[v] = e  # e is the tree edge that discovered v
                    next_level.append(v)  # v will be further considered in next pass
        level = next_level  # relabel 'next' level to become current


def bfs_complete(g):
    forest = {}
    for u in g.vertices():
        if u not in forest:
            forest[u] = None  # u will be a root of a tree
            bfs(g, u, forest)
    return forest
