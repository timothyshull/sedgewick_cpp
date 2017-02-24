def matrix_chain(d):
    n = len(d) - 1  # number of matrices
    n_by_n = [[0] * n for i in range(n)]  # initialize n-by-n result to zero
    for b in range(1, n):  # number of products in subchain
        for i in range(n - b):  # start of subchain
            j = i + b  # end of subchain
            n_by_n[i][j] = min(n_by_n[i][k] + n_by_n[k + 1][j] + d[i] * d[k + 1] * d[j + 1] for k in range(i, j))
    return n_by_n
