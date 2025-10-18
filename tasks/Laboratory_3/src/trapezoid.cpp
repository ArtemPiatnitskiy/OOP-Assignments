#include "../include/trapezoid.h"
#include "../include/point.h"

// Конструктор с параметрами описания и четырьмя точками.
Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4, std::string description)
    : Figure(description) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Trapezoid::operator==(const Trapezoid& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
auto Trapezoid::operator<=>(const Trapezoid& other) const {
    return this->square() <=> other.square();
}

Point Trapezoid::geometric_center() const {
    double center_x = (points[0].get_x() + points[2].get_x() + points[1].get_x() + points[3].get_x()) / 4.0;
    double center_y = (points[0].get_y() + points[2].get_y() + points[1].get_y() + points[3].get_y()) / 4.0;
    return Point(center_x, center_y);
}

double Trapezoid::square() const {
    // return (abs(points[0].get_x())) / 2.0;
}

double Trapezoid::perimeter() const {
    double length = distance(points[0], points[1]);
    double width = distance(points[0], points[3]);
    return 2 * (length + width);
}

Trapezoid::operator double() const {
    return this->square();
}

void Trapezoid::print(std::ostream& os) const {
    for (const auto& point : points) {
        os << point << std::endl;
    }
}

void Trapezoid::read(std::istream& is) {
    for (auto& point : points) {
        is >> point;
    }
}

Figure* Trapezoid::clone() const {
    return new Trapezoid(this->points[0], this->points[1], this->points[2], this->points[3]);
}