#ifndef SHAPE_H
#define SHAPEH

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using std::string;

class Shape{
protected:

public:
    Shape() {}
    virtual ~Shape(){}
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string name() const = 0;
    void print() const;
};

#endif