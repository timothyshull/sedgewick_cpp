#ifndef RESIZING_ARRAY_STACK_H
#define RESIZING_ARRAY_STACK_H

#include <vector>

template <typename T>
class Resizing_array_stack {
public:

Resizing_array_stack() {
        a = (Item[]) new Object[2];
        n = 0;
    }

bool is_empty() {
        return n == 0;
    }

int size() {
        return n;
    }


void push(Item item) {
        if (n == a.length) resize(2 * a.length);    // double size of array if necessary
        a[n++] = item;                            // add item
    }

Item pop() {
        if (is_empty()) throw new NoSuchElementException("Stack underflow");
        Item item = a[n - 1];
        a[n - 1] = null;                              // to avoid loitering
        n--;
        // shrink size of array if necessary
        if (n > 0 && n == a.length / 4) resize(a.length / 2);
        return item;
    }

Item peek() {
        if (is_empty()) throw new NoSuchElementException("Stack underflow");
        return a[n - 1];
    }
private:
    std::vector<T> a;
    int n;

void resize(int capacity) {
        assert capacity >= n;
        Item[] temp = (Item[]) new Object[capacity];
        for (int i = 0; i < n; ++i) {
            temp[i] = a[i];
        }
        a = temp;
    }
};

#endif // RESIZING_ARRAY_STACK_H
