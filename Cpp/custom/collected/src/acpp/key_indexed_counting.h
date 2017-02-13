// Program 6.17 - Key-indexed counting
#ifndef KEY_INDEXED_COUNTING_H
#define KEY_INDEXED_COUNTING_H

void distcount(int a[], int l, int r)
{
    int i, j, cnt[M];
    static int b[maxN];
    for (j = 0; j < M; j++) { cnt[j] = 0; }
    for (i = l; i <= r; i++) { cnt[a[i] + 1]++; }
    for (j = 1; j < M; j++) { cnt[j] += cnt[j - 1]; }
    for (i = l; i <= r; i++) { b[cnt[a[i]]++] = a[i]; }
    for (i = l; i <= r; i++) { a[i] = b[i - l]; }
}

#endif // KEY_INDEXED_COUNTING_H
