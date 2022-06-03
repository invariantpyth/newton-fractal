#include <vector>
#include <complex>

#ifndef NEWTON_FRACTAL_POLYNOMIAL_H
#define NEWTON_FRACTAL_POLYNOMIAL_H


class Polynomial
{

    std::vector <std::complex <double>> coefficients;
    size_t degree;


public:
    Polynomial(size_t degree, std::vector<std::complex<double>> coefficients);
    Polynomial(size_t degree, std::complex<double> factor, std::vector<std::complex<double>> roots);
    size_t getDegree() const;
    const std::vector<std::complex<double>> &getCoefficients() const;
    Polynomial derivative();
    std::complex <double> value(std::complex <double> c);

};


#endif //NEWTON_FRACTAL_POLYNOMIAL_H
