#pragma once
#include <string>
#include <initializer_list>

class Octal {
public:
    Octal();
    Octal(const size_t& n, unsigned char fill = 0);
    Octal(const std::initializer_list<unsigned char> &list);
    Octal(const std::string &octalString);
    Octal(const Octal &other); // Копи-конструктор
    Octal(Octal &&other) noexcept; // Конструктор перемещения
    virtual ~Octal(); // Деструктор


    Octal add(const Octal &other) const;
    Octal subtract(const Octal &other) const;


    Octal add_assign(const Octal &other) const;

    int compare(const Octal &other) const;
    bool equals(const Octal &other) const;
    bool less_than(const Octal &other) const;

    std::string to_string(const Octal &number) const;

    std::string to_string() const;
    size_t size() const;

private:
    size_t size_;
    unsigned char *digits_; // Массив цифр в восьмеричной системе, младший разряд - digits_[0]
    Octal normalize() const; // Удаляет ведущие нули
};