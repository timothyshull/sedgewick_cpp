#ifndef CH_4_9_APPLICATION_BASED_ADTS_POLY_ADT_H
#define CH_4_9_APPLICATION_BASED_ADTS_POLY_ADT_H

template<class Number>
class POLY {
private:
    // Implementation-dependent code
public:
    POLY<Number>(Number, int);

    float eval(float) const;

    friend POLY operator+(POLY &, POLY &);

    friend POLY operator*(POLY &, POLY &);
};

#endif //CH_4_9_APPLICATION_BASED_ADTS_POLY_ADT_H
