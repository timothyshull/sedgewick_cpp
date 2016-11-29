#ifndef CH_4_6_FIFO_QUEUES_ARRAY_QUEUE_H
#define CH_4_6_FIFO_QUEUES_ARRAY_QUEUE_H

template<class Item>
class QUEUE {
private:
    Item *q;
    int N, head, tail;
public:
    QUEUE(int maxN) {
        q = new Item[maxN + 1];
        N = maxN + 1;
        head = N;
        tail = 0;
    }

    int empty() const { return head % N == tail; }

    void put(Item item) {
        q[tail++] = item;
        tail = tail % N;
    }

    Item get() {
        head = head % N;
        return q[head++];
    }
};

#endif //CH_4_6_FIFO_QUEUES_ARRAY_QUEUE_H
