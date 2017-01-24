#ifndef RESIZING_ARRAY_QUEUE_H
#define RESIZING_ARRAY_QUEUE_H

#include <vector>

template<typename T>
class Resizing_array_queue {
public:
    Resizing_array_queue()
    {
        q = (Item[]) new Object[2];
        n = 0;
        first = 0;
        last = 0;
    }

    bool isEmpty()
    {
        return n == 0;
    }

    int size()
    {
        return n;
    }

    void enqueue(Item item)
    {
        // double size of array if necessary and recopy to front of array
        if (n == q.length) { resize(2 * q.length); }   // double size of array if necessary
        q[last++] = item;                        // add item
        if (last == q.length) last = 0;          // wrap-around
        n++;
    }

    Item dequeue()
    {
        if (isEmpty()) { throw new NoSuchElementException("Queue underflow"); }
        Item item = q[first];
        q[first] = null;                            // to avoid loitering
        n--;
        first++;
        if (first == q.length) { first = 0; }           // wrap-around
        // shrink size of array if necessary
        if (n > 0 && n == q.length / 4) resize(q.length / 2);
        return item;
    }

    Item peek()
    {
        if (isEmpty()) { throw new NoSuchElementException("Queue underflow"); }
        return q[first];
    }

private:
    std::vector<T> q;
    int n;
    int first;
    int last;

    void resize(int capacity)
    {
        assert
        capacity >= n;
        Item[]
        temp = (Item[])
        new Object[capacity];
        for (int i = 0; i < n; i++) {
            temp[i] = q[(first + i) % q.length];
        }
        q = temp;
        first = 0;
        last = n;
    }
};

#endif // RESIZING_ARRAY_QUEUE_H
