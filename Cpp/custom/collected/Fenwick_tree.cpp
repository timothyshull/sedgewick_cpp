#include "Fenwick_tree.h"

Fenwick_tree::Fenwick_tree(int size){
    array = new int[size + 1];
}

int Fenwick_tree::rsq(int a, int b)
{
    assert ind > 0;
    int sum = 0;
    while (ind > 0) {
        sum += array[ind];
        //Extracting the portion up to the first significant one of the binary representation of 'ind' and decrementing ind by that number
        ind -= ind & (-ind);
    }

    return sum;
}

int Fenwick_tree::rsq(int a, int b) {
    assert b >= a && a > 0 && b > 0;

    return rsq(b) - rsq(a - 1);
}

void Fenwick_tree::update(int ind, int value)
{
    assert ind > 0;
    while (ind < array.length) {
        array[ind] += value;
        //Extracting the portion up to the first significant one of the binary representation of 'ind' and incrementing ind by that number
        ind += ind & (-ind);
    }
}

int Fenwick_tree::size()
{
    return array.size() - 1;
}
