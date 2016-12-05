from . import five_one_walk_connected_graph

walk = five_one_walk_connected_graph.walk


def components(g):
    comp = []
    seen = set()
    for u in g:
        if u in seen: continue
        c = walk(g, u)
        seen.update(c)
        comp.append(c)
    return comp
