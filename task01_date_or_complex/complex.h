#include <iostream>
#include <algorithm>
#include <cmath>

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{
private:
    double real;
    double imag;
public:
    Complex(): real(0), imag(0) {}
    Complex(double re, double im) : real(re), imag(im) {}
    double get_re() const;
    double get_im() const;
    Complex& set_re(double newre);
    Complex& set_im(double newim);
    Complex operator+(const Complex& b) const;
    Complex operator-(const Complex& b) const;
    Complex operator*(const Complex& b) const;
    Complex operator/(const Complex& b) const;
};

#endif