#include "complex.h"

double Complex::get_re() const {
    return real;
}

double Complex::get_im() const {
    return imag;
}

Complex& Complex::set_re(double newre){
    real = newre;
    return *this;
}

Complex& Complex::set_im(double newim){
    imag = newim;
    return *this;
}

Complex Complex::operator+(const Complex& b) const {
    Complex res(real + b.real, imag + b.imag);
    return res;
}
Complex Complex::operator-(const Complex& b) const {
    Complex res(real - b.real, imag - b.imag);
    return res;
}
Complex Complex::operator*(const Complex& b) const {
    double tmp1, tmp2;
    tmp1 = real*b.real - imag*b.imag;
    tmp2 = real*b.imag + imag*b.real;
    Complex res(tmp1, tmp2);
    return res;
}
Complex Complex::operator/(const Complex& b) const {
    Complex b_(b.real, -b.imag);
    Complex son = *this *b_;
    Complex fa = b*b_;
    double tmp = fa.real;
    if(tmp == 0){
        std::cout << "/ is error " << '\n';
        return *this;
    }
    Complex res(son.real/tmp, son.imag/tmp);
    return res;
}

Complex Complex::operator/(const double& b) const{
    if(b == 0) {
        std::cout << "b == 0" << '\n';
        return *this;
    }
    Complex res(real/b, imag/b);
    return res;
}

Complex& Complex::operator+=(const Complex& b){
    real += b.real;
    imag += b.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& b){
    real -= b.real;
    imag -= b.imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& b){
    Complex tmp = *this *b;
    real = tmp.real;
    imag = tmp.imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& b){
    Complex tmp = *this /b;
    real = tmp.real;
    imag = tmp.imag;
    return *this;
}

Complex Complex::get_conj() const{
    return Complex(real, -imag);
}

double Complex::get_abs() const{
    return std::sqrt(real*real + imag*imag);   
}

bool Complex::operator==(const Complex& b) const{
    double eps = 1e-9;
    if(std::abs(real - b.real) > eps) return false;
    if(std::abs(imag - b.imag) > eps) return false;
    return true;
}

bool Complex::operator!=(const Complex& b) const{
    if(*this == b) return false;
    return true;
}

Complex operator+(double a, const Complex& b){
    Complex tmp(a+b.real, b.imag);
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Complex& a){
    if(a.real != 0 && a.imag != 0){
        if(a.imag > 0)
            os << a.real << '+' << a.imag << 'i';
        else
            os << a.real << a.imag << 'i';
        return os;
    }
    if(a.real == 0 && a.imag != 0){
        os << a.imag << 'i';
        return os;
    }
    if(a.real != 0 && a.imag == 0){
        os << a.real;
        return os;
    }
    if(a.real == 0 && a.imag == 0){
        os << 0;
        return os;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Complex& a){
    double re, im;
    if(is >> re >> im){
        a.real = re;
        a.imag = im;
    }
    return is;
}