#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape{
private:
    double b;
public:
    Square(): b(1.0) {}
    Square(double b_) : b(b_) {}
    ~Square() {}
    double area() const override;
    double perimeter() const override;
    string name() const override;
    double get_b() const ;
};

#endif