#include "../include/point.h"
#include <iostream>

inline std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.point_x << ", " << point.point_y << ")";
    return os;
}

inline std::istream& operator>>(std::istream& is, Point& point) {
    char delimetr;
    double x, y;
    is >> delimetr >> x >> delimetr >> y >> delimetr;
    return is;
}

Point::Point(double p_x, double p_y): point_x(p_x), point_y(p_y) {}

double Point::get_x() const {
    return point_x;
}

double Point::get_y() const {
    return point_y;
}

void Point::Point::move(double new_x, double new_y) {
    point_x = new_x;
    point_y = new_y;
}