from ..ch09.adaptable_heap_priority_queue import AdaptableHeapPriorityQueue


def shortest_path_lengths(g, src):
    d = dict()  # d[v] is upper bound from s to v
    cloud = dict()  # map reachable v to its d[v] value
    pq = AdaptableHeapPriorityQueue()  # vertex v will have key d[v]
    pq_locator = dict()  # map from vertex to its pq locator

    # for each vertex v of the graph, add an entry to the priority queue, with
    # the source having distance 0 and all others having infinite distance
    for v in g.vertices():
        if v is src:
            d[v] = 0
        else:
            d[v] = float('inf')  # syntax for positive infinity
        pq_locator[v] = pq.add(d[v], v)  # save locator for future updates

    while not pq.is_empty():
        key, u = pq.remove_min()
        cloud[u] = key  # its correct d[u] value
        del pq_locator[u]  # u is no longer in pq
        for e in g.incident_edges(u):  # outgoing edges (u,v)
            v = e.opposite(u)
            if v not in cloud:
                # perform relaxation step on edge (u,v)
                wgt = e.element()
                if d[u] + wgt < d[v]:  # better path to v?
                    d[v] = d[u] + wgt  # update the distance
                    pq.update(pq_locator[v], d[v], v)  # update the pq entry

    return cloud  # only includes reachable vertices


def shortest_path_tree(g, s, d):
    tree = dict()
    for v in d:
        if v is not s:
            for e in g.incident_edges(v, False):  # consider INCOMING edges
                u = e.opposite(v)
                wgt = e.element()
                if d[v] == d[u] + wgt:
                    tree[v] = e  # edge e is used to reach v
    return tree
