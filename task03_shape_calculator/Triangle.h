#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <algorithm>

class Triangle : public Shape{
private:
    double a;
    double b;
    double c;
public:
    Triangle(): a(5.0) , b(4.0) , c(3.0) {}
    Triangle(double a_, double b_, double c_);
    ~Triangle() {}
    double area() const override;
    double perimeter() const override;
    string name() const override;
    double get_a() const ;
    double get_b() const;
    double get_c() const;
};

#endif