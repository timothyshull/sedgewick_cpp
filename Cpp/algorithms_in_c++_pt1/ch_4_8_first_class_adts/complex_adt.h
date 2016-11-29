#ifndef CH_4_8_FIRST_CLASS_ADTS_COMPLEX_ADT_H
#define CH_4_8_FIRST_CLASS_ADTS_COMPLEX_ADT_H

class Complex {
private:
    // Implementation-dependent code
public:
    Complex(float, float);

    float Re() const;

    float Im() const;

    Complex &operator*=(Complex &);
};

#endif //CH_4_8_FIRST_CLASS_ADTS_COMPLEX_ADT_H
