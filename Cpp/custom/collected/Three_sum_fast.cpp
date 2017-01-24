#include "Three_sum_fast.h"

bool ::Three_sum_fast::containsDuplicates(std::vector<int>& a)
{
    for (int i = 1; i < a.length; i++)
        if (a[i] == a[i - 1]) return true;
    return false;
}

void ::Three_sum_fast::printAll(std::vector<int>& a)
{
    int n = a.length;
    Arrays.sort(a);
    if (containsDuplicates(a)) throw new IllegalArgumentException("array contains duplicate integers");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = Arrays.binarySearch(a, -(a[i] + a[j]));
            if (k > j) StdOut.println(a[i] + " " + a[j] + " " + a[k]);
        }
    }
}

int ::Three_sum_fast::count(std::vector<int>& a)
{
    int n = a.length;
    Arrays.sort(a);
    if (containsDuplicates(a)) throw new IllegalArgumentException("array contains duplicate integers");
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = Arrays.binarySearch(a, -(a[i] + a[j]));
            if (k > j) count++;
        }
    }
    return count;
}
