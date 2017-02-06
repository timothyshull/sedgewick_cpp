#include "Horners_method.h"

double ::Horners_method::horner_eval(double x, std::vector<double>& coeff, unsigned degree)
{
    double result{0.0};
    int i;
    for (i = degree; i >= 0; --i) {
        result = result * x + coeff[i];
    }
    return result;
}