#include "Horners_method.h"

// assumes coefficients in order c0, c1, c2, ..., cn for polynomial cn*x^n + ... + c1*x + c0
double ::Horners_method::horner_eval(double x, std::vector<double>& coeff)
{
    double result{0.0};
    for (auto i = coeff.size() - 1; i >= 0; --i) { result = result * x + coeff[i]; }
    return result;
}