#include "Segment_tree.h"

int Segment_tree_node::size()
{
    return to - from + 1;
}

Segment_tree::Segment_tree(std::vector<int>& array)
{
    this.array = Arrays.copyOf(array, array.length);
    //The max size of this array is about 2 * 2 ^ log2(_size) + 1
    size = (int) (2 * std::pow(2.0, std::floor((std::log((double) array.length) / std::log(2.0)) + 1)));
    heap = new Node[size];
    build(1, 0, array.length);
}

int Segment_tree::size()
{
    return array.length;
}

int Segment_tree::rsq(int from, int to)
{
    return rsq(1, from, to);
}

int Segment_tree::rMinQ(int from, int to)
{
    return rMinQ(1, from, to);
}

void Segment_tree::update(int from, int to, int value)
{
    update(1, from, to, value);
}

int Segment_tree::rsq(int v, int from, int to)
{
    Node n = heap[v];

    //If you did a range update that contained this node, you can infer the Sum without going down the tree
    if (n.pendingVal != null && contains(n.from, n.to, from, to)) {
        return (to - from + 1) * n.pendingVal;
    }

    if (contains(from, to, n.from, n.to)) {
        return heap[v].sum;
    }

    if (intersects(from, to, n.from, n.to)) {
        propagate(v);
        int leftSum = rsq(2 * v, from, to);
        int rightSum = rsq(2 * v + 1, from, to);

        return leftSum + rightSum;
    }

    return 0;
}

void Segment_tree::build(int v, int from, int size)
{
    heap[v] = new Node();
    heap[v].from = from;
    heap[v].to = from + size - 1;

    if (size == 1) {
        heap[v].sum = array[from];
        heap[v].min = array[from];
    } else {
        //Build childs
        build(2 * v, from, size / 2);
        build(2 * v + 1, from + size / 2, size - size / 2);

        heap[v].sum = heap[2 * v].sum + heap[2 * v + 1].sum;
        //min = min of the children
        heap[v].min = std::min(heap[2 * v].min, heap[2 * v + 1].min);
    }
}

int Segment_tree::rMinQ(int v, int from, int to)
{
    Node n = heap[v];

    //If you did a range update that contained this node, you can infer the Min value without going down the tree
    if (n.pendingVal != null && contains(n.from, n.to, from, to)) {
        return n.pendingVal;
    }

    if (contains(from, to, n.from, n.to)) {
        return heap[v].min;
    }

    if (intersects(from, to, n.from, n.to)) {
        propagate(v);
        int leftMin = rMinQ(2 * v, from, to);
        int rightMin = rMinQ(2 * v + 1, from, to);

        return std::min(leftMin, rightMin);
    }

    return Integer.MAX_VALUE;
}

void Segment_tree::update(int v, int from, int to, int value)
{
    Node n = heap[v];

    if (contains(from, to, n.from, n.to)) {
        change(n, value);
    }

    if (n.size() == 1) return;

    if (intersects(from, to, n.from, n.to)) {
        propagate(v);

        update(2 * v, from, to, value);
        update(2 * v + 1, from, to, value);

        n.sum = heap[2 * v].sum + heap[2 * v + 1].sum;
        n.min = std::min(heap[2 * v].min, heap[2 * v + 1].min);
    }
}

void Segment_tree::propagate(int v)
{
    Node n = heap[v];

    if (n.pendingVal != null) {
        change(heap[2 * v], n.pendingVal);
        change(heap[2 * v + 1], n.pendingVal);
        n.pendingVal = null; //unset the pending propagation value
    }
}

void Segment_tree::change(Segment_tree_node* n, int value)
{
    n.pendingVal = value;
    n.sum = n.size() * value;
    n.min = value;
    array[n.from] = value;
}

bool Segment_tree::contains(int from1, int to1, int from2, int to2)
{
    return from2 >= from1 && to2 <= to1;
}

bool Segment_tree::intersects(int from1, int to1, int from2, int to2) {
    return from1 <= from2 && to1 >= from2 || from1 >= from2 && from1 <= to2;
}