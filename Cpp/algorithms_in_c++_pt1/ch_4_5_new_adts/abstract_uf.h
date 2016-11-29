#ifndef CH_4_5_NEW_ADTS_ABSTRACT_UF_H
#define CH_4_5_NEW_ADTS_ABSTRACT_UF_H

class uf {
public:
    virtual uf(int) = 0;

    virtual int find(int, int) = 0;

    virtual void unite(int, int) = 0;
};

#endif //CH_4_5_NEW_ADTS_ABSTRACT_UF_H
