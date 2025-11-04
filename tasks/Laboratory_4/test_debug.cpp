#include <iostream>
#include <cmath>
#include "include/rhombus.h"
#include "include/point.h"

int main() {
    Point<double> p1(0.0, 1.0);
    Point<double> p2(-1.0, 0.0);
    Point<double> p3(0.0, -1.0);
    Point<double> p4(1.0, 0.0);
    
    Rhombus<double> rhombus1(p1, p2, p3, p4);
    
    Point<double> p5(0.0, std::sqrt(2.0));
    Point<double> p6(-std::sqrt(2.0), 0.0);
    Point<double> p7(0.0, -std::sqrt(2.0));
    Point<double> p8(std::sqrt(2.0), 0.0);
    
    Rhombus<double> rhombus2(p5, p6, p7, p8);
    
    std::cout << "Rhombus1 square: " << rhombus1.square() << std::endl;
    std::cout << "Rhombus2 square: " << rhombus2.square() << std::endl;
    std::cout << "Difference: " << std::abs(rhombus1.square() - rhombus2.square()) << std::endl;
    std::cout << "Are equal: " << (rhombus1 == rhombus2) << std::endl;
    
    return 0;
}
