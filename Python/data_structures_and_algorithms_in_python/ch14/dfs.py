def dfs(g, u, discovered):
    for e in g.incident_edges(u):  # for every outgoing edge from u
        v = e.opposite(u)
        if v not in discovered:  # v is an unvisited vertex
            discovered[v] = e  # e is the tree edge that discovered v
            dfs(g, v, discovered)  # recursively explore from v


def construct_path(u, v, discovered):
    path = list()  # empty path by default
    if v in discovered:
        # we build list from v to u and then reverse it at the end
        path.append(v)
        walk = v
        while walk is not u:
            e = discovered[walk]  # find edge leading to walk
            parent = e.opposite(walk)
            path.append(parent)
            walk = parent
        path.reverse()  # reorient path from u to v
    return path


def dfs_complete(g):
    forest = dict()
    for u in g.vertices():
        if u not in forest:
            forest[u] = None  # u will be the root of a tree
            dfs(g, u, forest)
    return forest

