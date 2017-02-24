def lcs(X, Y):
    n, m = len(X), len(Y)  # introduce convenient notations
    L = [[0] * (m + 1) for k in range(n + 1)]  # (n+1) x (m+1) table
    for j in range(n):
        for k in range(m):
            if X[j] == Y[k]:  # align this match
                L[j + 1][k + 1] = L[j][k] + 1
            else:  # choose to ignore one character
                L[j + 1][k + 1] = max(L[j][k + 1], L[j + 1][k])
    return L


def lcs_solution(X, Y, L):
    solution = []
    j, k = len(X), len(Y)
    while L[j][k] > 0:  # common characters remain
        if X[j - 1] == Y[k - 1]:
            solution.append(X[j - 1])
            j -= 1
            k -= 1
        elif L[j - 1][k] >= L[j][k - 1]:
            j -= 1
        else:
            k -= 1
    return ''.join(reversed(solution))  # return left-to-right version
