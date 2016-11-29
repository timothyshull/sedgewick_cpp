#ifndef CH_4_6_FIFO_QUEUES_QUEUE_ADT_H
#define CH_4_6_FIFO_QUEUES_QUEUE_ADT_H

template<class Item>
class QUEUE {
private:
    // Implementation-dependent code
public:
    QUEUE(int);

    int empty();

    void put(Item);

    Item get();
};

#endif //CH_4_6_FIFO_QUEUES_QUEUE_ADT_H
