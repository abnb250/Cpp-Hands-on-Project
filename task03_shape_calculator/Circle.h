#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape{
private:
    double r;
public:
    Circle(): Shape(), r(1.0) {}
    Circle(double r_) : Shape(), r(r_) {}
    ~Circle() {}
    double area() const override;
    double perimeter() const override;
    string name() const override;
    double get_r() const ;
    double get_d() const;
};

#endif