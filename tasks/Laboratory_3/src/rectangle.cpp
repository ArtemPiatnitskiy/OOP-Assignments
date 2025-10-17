#include "../include/rectangle.h"

// Конструктор с параметрами описания и двумя точками противоположных углов.
Rectangle::Rectangle(std::string description, const Point& p1, const Point& p2, std::string discription)
    : Figure(description) {
    points[0] = p1;
    points[1] = Point(p2.get_x(), p1.get_y());
    points[2] = p2;
    points[3] = Point(p1.get_x(), p2.get_y());
}

// Перегрузка операторов = копирования и перемещения.
// Конструктор копирования.
Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

// Конструктор перемещения.
Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

// Перегрузка оператора сравниения ==.
bool Rectangle::operator==(const Rectangle& other) const {
    if (this->square() != other.square()) {
        return false;
    }
    return true;
}

// Перегрузка оператора сравнения <=>
auto Rectangle::operator<=>(const Rectangle& other) const {
    return this->square() <=> other.square();
}