#include "Triangle.h"
#include <algorithm>

Triangle::Triangle(double a_, double b_, double c_){
    double tmp[3] = {a_, b_, c_};
    std::sort(tmp, tmp + 3);
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];
}

double Triangle::area() const {
    double p = perimeter()/2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

double Triangle::perimeter() const {
    return a+b+c;
}

string Triangle::name() const {
    return "Triangle";
}

double Triangle::get_a() const{
    return a;
}

double Triangle::get_b() const{
    return b;
}

double Triangle::get_c() const{
    return c;
}