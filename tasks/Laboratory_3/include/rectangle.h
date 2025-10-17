#pragma once
#include <string>
#include "point.h"
#include "figure.h"

class Rectangle : public Figure {
    public:
        // Конструктор по умолчанию.
        Rectangle() : Figure("rectangle") {};
        
        // Конструктор точками противоположных углов.
        Rectangle(std::string description, const Point& p1, const Point& p2, std::string discription = "rectangle");

        // Перегрузка операторов = копирования и перемещения.
        // Конструктор копирования.
        Rectangle& operator=(const Rectangle& other);
        // Конструктор перемещения.
        Rectangle& operator=(Rectangle&& other) noexcept;

        // Перегрузка оператора сравниния ==.
        bool operator==(const Rectangle& other) const;
        // Перегрузка оператора сравнения <=>
        auto operator<=>(const Rectangle& other) const;

        // Переопределение виртуальных методов базового класса.
        double geometric_center() const override;
        double square() const override;
        double perimeter() const override;

        // Функция для нахождения площади фигуры через перегрузку оператора double().
        // Возвращает площадь фигуры.
        // Мы не используем explicit здесь, чтобы позволить неявное преобразование к double.
        operator double() const;

        // Перегрузка операторов ввода/вывода.
        void print(std::ostream& os) const override;
        void read(std::istream& is) override;

        // Функция для клонирования фигуры.
        Figure* clone() const override;

    private:
        Point points[4];

};