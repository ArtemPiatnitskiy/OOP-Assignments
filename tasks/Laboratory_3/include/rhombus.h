#pragma once
#include <string>
#include "point.h"
#include "figure.h"

class Rhombus : public Figure {
    public:
        // Конструктор по умолчанию.
        Rhombus() = default;
        // Конструктор точками.
        Rhombus(std::string description, const Point& p1, const Point& p2, const Point& p3, const Point& p4);

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Rhombus& operator=(const Rhombus& other);
        // Конструктор перемещения.
        Rhombus& operator=(Rhombus&& other) noexcept;

        // Перегрузка оператора сравниения ==.
        bool operator==(const Rhombus& other) const;
        // Перегрузка оператора сравнения <=>
        auto operator<=>(const Rhombus& other) const;

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