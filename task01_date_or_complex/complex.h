#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <algorithm>
#include <cmath>

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
    Complex operator/(const double& b) const;
    Complex& operator+=(const Complex& b);
    Complex& operator-=(const Complex& b);
    Complex& operator*=(const Complex& b);
    Complex& operator/=(const Complex& b);
    Complex get_conj() const;
    double get_abs() const;
    bool operator==(const Complex& b) const;
    bool operator!=(const Complex& b) const;
    friend Complex operator+(double a, const Complex& b);
    friend std::ostream& operator<<(std::ostream& os, const Complex& a);
    friend std::istream& operator>>(std::istream& is, Complex& a);
};

#endif