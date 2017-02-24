def disjoint1(iter_a, iter_b, iter_c):
    for a in iter_a:
        for b in iter_b:
            for c in iter_c:
                if a == b == c:
                    return False  # we found a common value
    return True  # if we reach this, sets are disjoint


def disjoint2(iter_a, iter_b, iter_c):
    for a in iter_a:
        for b in iter_b:
            if a == b:  # only check C if we found match from A and B
                for c in iter_c:
                    if a == c:  # (and thus a == b == c)
                        return False  # we found a common value
    return True  # if we reach this, sets are disjoint
