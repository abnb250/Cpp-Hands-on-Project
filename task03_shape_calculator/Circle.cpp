#include "Circle.h"

double Circle::area() const {
    return 3.14159 * r * r;
}

double Circle::perimeter() const {
    return 2*3.14159*r;
}

string Circle::name() const {
    return "Circle";
}

double Circle::get_r() const{
    return r;
}

double Circle::get_d() const{
    return r*2;
}