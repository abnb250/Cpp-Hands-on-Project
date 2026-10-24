#include "Square.h"

double Square::area() const {
    return b*b;
}

double Square::perimeter() const {
    return 4*b;
}

string Square::name() const {
    return "Square";
}

double Square::get_b() const{
    return b;
}

