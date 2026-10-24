#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape{
private:
    double l;
    double s;
public:
    Rectangle(): l(2.0), s(1.0) {}
    Rectangle(double l_, double s_) : l(l_), s(s_) {}
    ~Rectangle() {}
    double area() const override;
    double perimeter() const override;
    string name() const override;
    double get_l() const ;
    double get_s() const;
};

#endif