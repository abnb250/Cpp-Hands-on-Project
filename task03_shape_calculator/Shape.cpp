#include "Shape.h"
#include <iomanip>

void Shape::print() const {
    std::cout << "name: " << name() << '\n';
    std::cout << std::fixed << std::setprecision(2) << "area: " << area() << '\n';
    std::cout << std::fixed << std::setprecision(2) << "perimeter: " << perimeter() << '\n';
}