#ifndef CH_4_7_DUPLICATE_AND_INDEX_ITEMS_STACK_H
#define CH_4_7_DUPLICATE_AND_INDEX_ITEMS_STACK_H

template<class Item>
class STACK {
private:
    Item *s, *t;
    int N;
public:
    STACK(int maxN) {
        s = new Item[maxN];
        N = 0;
        t = new Item[maxN];
        for (int i = 0; i < maxN; i++) t[i] = 0;
    }

    int empty() const { return N == 0; }

    void push(Item item) {
        if (t[item] == 1) return;
        s[N++] = item;
        t[item] = 1;
    }

    Item pop() {
        t[s[--N]] = 0;
        return s[N];
    }
};

#endif //CH_4_7_DUPLICATE_AND_INDEX_ITEMS_STACK_H
