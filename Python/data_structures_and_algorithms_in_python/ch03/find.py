def find(S, val):
    n = len(S)
    j = 0
    while j < n:
        if S[j] == val:
            return j  # a match was found at index j
        j += 1
    return -1
