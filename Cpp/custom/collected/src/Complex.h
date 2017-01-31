#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
public:
    Complex(double real, double imaginary);

    std::string to_string() const;

    double abs() const;

    double phase() const;

    Complex plus(Complex& that) const;

    Complex minus(Complex& that) const;

    Complex times(Complex& that) const;

    Complex scale(double alpha) const;

    Complex times(double alpha) const;

    Complex conjugate() const;

    Complex reciprocal() const;

    inline double real() const { return _real; };

    inline double imaginary() const { return _imaginary; }

    Complex divides(Complex& that) const;

    Complex exp() const;

    Complex sin() const;

    Complex cos() const;

    Complex tan() const;
private:
    double _real;
    double _imaginary;
};

std::ostream& operator<<(std::ostream& os, Complex& out);

#endif // COMPLEX_H
