#ifndef CH_4_8_FIRST_CLASS_ADTS_QUEUE_ADT_H
#define CH_4_8_FIRST_CLASS_ADTS_QUEUE_ADT_H

template<class Item>
class QUEUE {
private:
    // Implementation-dependent code
public:
    QUEUE(int);

    QUEUE(const QUEUE &);

    QUEUE &operator=(const QUEUE &);

    ~QUEUE();

    int empty() const;

    void put(Item);

    Item get();
};

#endif //CH_4_8_FIRST_CLASS_ADTS_QUEUE_ADT_H
