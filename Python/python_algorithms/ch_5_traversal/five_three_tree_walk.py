def tree_walk(t, r):
    for u in t[r]:
        tree_walk(t, u)
