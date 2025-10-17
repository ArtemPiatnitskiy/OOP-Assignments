#pragma once
#include <string>
#include "point.h"
#include "figure.h"

class Trapezoid : public Figure {
    public:
        // Конструктор по умолчанию.
        Trapezoid() = default;
        // Конструктор точками.
        Trapezoid(std::string description, const Point& p1, const Point& p2, const Point& p3, const Point& p4);

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Trapezoid& operator=(const Trapezoid& other);
        // Конструктор перемещения.
        Trapezoid& operator=(Trapezoid&& other) noexcept;

        // Перегрузка оператора сравниения ==.
        bool operator==(const Trapezoid& other) const;
        // Перегрузка оператора сравнения <=>
        auto operator<=>(const Trapezoid& other) const;

        // Переопределение виртуальных методов базового класса.
        double geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        operator double() const;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[4];

};