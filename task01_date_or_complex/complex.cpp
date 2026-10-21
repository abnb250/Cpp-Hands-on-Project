#include "complex.h"

double Complex::get_re() const {
    return real;
}

double Complex::get_im() const {
    return imag;
}

Complex& Complex::set_re(double newre){
    real = newre;
}

Complex& Complex::set_im(double newim){
    imag = newim;
}

Complex Complex::operator+(const Complex& b) const {}
Complex Complex::operator-(const Complex& b) const {}
Complex Complex::operator*(const Complex& b) const {}
Complex Complex::operator/(const Complex& b) const {}