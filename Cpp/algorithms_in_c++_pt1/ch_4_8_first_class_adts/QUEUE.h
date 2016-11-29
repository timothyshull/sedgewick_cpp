#ifndef CH_4_8_FIRST_CLASS_ADTS_QUEUE_H
#define CH_4_8_FIRST_CLASS_ADTS_QUEUE_H

template<class Item>
class QUEUE {
private:
    void deletelist() {
        for (link t = head; t != 0; head = t) {
            t = head->next;
            delete head;
        }
    }

public:
    QUEUE(int);

    QUEUE(const QUEUE &rhs) {
        head = 0;
        *this = rhs;
    }

    QUEUE &operator=(const QUEUE &rhs) {
        if (this == &rhs) return *this;
        deletelist();
        link t = rhs.head;
        while (t != 0) {
            put(t->item);
            t = t->next;
        }
        return *this;
    }

    ~QUEUE() { deletelist(); }

    int empty() const;

    void put(Item);

    Item get();
};

#endif //CH_4_8_FIRST_CLASS_ADTS_QUEUE_H
