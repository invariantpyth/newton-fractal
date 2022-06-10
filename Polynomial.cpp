#include <utility>
#include "Polynomial.h"


// Constructs a polynomial from roots and multiplies it with a factor
Polynomial::Polynomial(size_t degree, std::complex<double> factor, std::vector<std::complex<double>> roots)
{
    this->degree = roots.size();
    std::vector <std::complex <double>> coeffs(this->degree + 1, 0);
    coeffs[1] = 1;
    coeffs[0] = -roots[0];
    for (size_t k = 2; k <= this->degree; k++)
    {
        coeffs[k] = coeffs[k - 1];
        for (size_t i = k - 1; i > 0; i--)
        {
            coeffs[i] = coeffs[i - 1] -
                        coeffs[i] * roots[k - 1];
        }
        coeffs[0] = -coeffs[0] * roots[k - 1];
    }
    if (factor != (std::complex<double>)1){
        for (auto & coeff : coeffs) {
            coeff = coeff * factor;
        }

    }
    this->coefficients = coeffs;
}


// Constructs a polynomial from coefficients
Polynomial::Polynomial(size_t degree, std::vector<std::complex<double>> coefficients) {
    this->degree = degree;
    this->coefficients = std::move(coefficients);
}


// Returns the derivative of a polynomial
Polynomial Polynomial::derivative()
{
    std::vector <std::complex <double>> derived_coeffs(this->degree, 0);
    for (size_t counter = 0; counter < degree; counter++)
    {
        derived_coeffs[counter] = coefficients[counter + 1] * (std::complex <double>)(counter + 1);
    }
    Polynomial dp {degree - 1, derived_coeffs};
    return dp;
}


// Returns value of the polynomial in c
std::complex<double> Polynomial::value(std::complex <double> c)
{
    std::complex<double> result;

    if (c == (std::complex <double> )0)
    {
        return this->coefficients[0];
    }

    for (size_t index = 0; index < this->degree + 1; index++){
        result += this->coefficients[index] * pow(c, index);
    }
    return result;
}

Polynomial::Polynomial(size_t degree) {
    this->degree = degree;
    this->coefficients = std::vector<std::complex<double>>(degree + 1, 0);
    this->coefficients[0] = 1;
    this->coefficients[degree] = 1;
}


// Counts iterations of the Newton's algorithm for point c and polynomial p
int Polynomial::newton(std::complex<double> c, double epsilon, int max_iter) {
    std::complex<double> xn = c;
    Polynomial dp = this->derivative();
    for (int counter = 0; counter < max_iter; counter++)
    {
        std::complex <double> f = this->value(c);

        if (abs(f) < epsilon)
        {
            return counter;
        }

        std::complex<double> df = dp.value(c);

        if (df == (std::complex<double>)0)
        {
            return 0;
        }
        else
        {
            xn = xn - (f / df);
        }
    }
    return 255;
}


Polynomial::~Polynomial() = default;


