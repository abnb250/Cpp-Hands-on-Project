#include "Rectangle.h"

double Rectangle::area() const {
    return l*s;
}

double Rectangle::perimeter() const {
    return 2*(l + s);
}

string Rectangle::name() const {
    return "Rectangle";
}

double Rectangle::get_l() const{
    return l;
}

double Rectangle::get_s() const{
    return s;
}