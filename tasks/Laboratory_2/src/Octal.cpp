#include "../include/Octal.h"
#include <stdexcept>
#include <algorithm>
// #include <cstring>

// Конструктор по умолчанию
Octal::Octal() : size_(1), digits_(new unsigned char[1]{0}) {}

// Конструктор с размером и заполнением
Octal::Octal(const size_t& n, unsigned char fill) {
    if (n == 0) {
        throw std::invalid_argument("Size must be greater than 0");
    }
    if (fill > 7) {
        throw std::invalid_argument("fill must be between 0 and 7");
    }
    else {
        size_ = n;
        digits_ = new unsigned char[size_];
        std::fill(digits_, digits_ + size_, fill); // Заполнение масива с помощью std::fill из библиотеки <algorithm> (про неё можно почитать в materials.md)
    }
}

// Конструктор с initializer_list
// Если список пустой, создаём число 0
// При вызове Octal{1, 2, 3} - создаётся число 321 (так как младший разряд будет в digits_[0])
Octal::Octal(const std::initializer_list<unsigned char> &list) : size_(0), digits_(nullptr) {
    if (list.size() == 0) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    size_ = list.size();
    digits_ = new unsigned char[size_];
    std::copy(list.begin(), list.end(), digits_); // Копирование элементов из initializer_list в массив digits_ используется функция std::copy из <algorithm>, про неё можно почитать в materials.md
    for (size_t i = 0; i < size_; ++i) {
        if (digits_[i] > 7) {
            delete[] digits_;
            throw std::invalid_argument("All digits must be between 0 and 7");
        }
    }
}

// Конструктор из строки
Octal::Octal(const std::string &octalString) {
    if (octalString.empty()) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    size_ = octalString.size();
    digits_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i) {
        if (octalString[size_ - 1 - i] > '7' || octalString[size_ - 1 - i] < '0') { // Мы двигаемся с конца, чтобы младший разряд был в digits_[0]
            delete[] digits_;
            throw std::invalid_argument("All digits must be between 0 and 7");
        }
        digits_[i] = octalString[size_ - 1 - i] - '0'; // Преобразование символов в числовые значения и реверс
    }
}

// Копи-конструктор
Octal::Octal(const Octal &other) : size_(other.size_), digits_(new unsigned char[other.size_]) {
    std::copy(other.digits_, other.digits_ + other.size_, digits_);
}

// Конструктор перемещения
Octal::Octal(Octal &&other) noexcept : size_(other.size_), digits_(other.digits_) {
    other.size_ = 1;
    other.digits_ = new unsigned char[1]{0};
}

// Деструктор
Octal::~Octal() {
    delete[] digits_;
}

// Нормализация
// Вариант 1 с изменением текущего объекта есть в materials.md, но это получается не const метод, поэтому мы делаем метод с возвратом нового объекта
// Вариант 2 (реализованный ниже) - создание нового объекта без ведущих нулей
Octal Octal::normalize() const {
    if (size_ == 0) {
        return Octal(); // Возвращаем 0
    }
    size_t new_size = size_;

    while (new_size > 1 && digits_[new_size - 1] == 0) --new_size; // Уменьшаем размер, пока старший разряд 0
    if (new_size == size_) {
        return *this; // Если размер не изменился, возвращаем текущий объект
    }
    Octal normalized_octal(new_size);
    std::copy(digits_, digits_ + new_size, normalized_octal.digits_);
    return normalized_octal;
}


// Сложение
// Вариант 1 с использованием временного unique_ptr будет в materials.md
// Вариант 2 (реализованный ниже) - с использованием обычного массива
Octal Octal::add(const Octal &other) const {
    size_t max_size = std::max(size_, other.size_);
    Octal result(max_size + 1, 0); // +1 на случай переноса в старший разряд
    unsigned int carry = 0; // Перенос в следующий разряд
    unsigned int temp_sum = 0; // Временная сумма для текущего разряда
    for (size_t i = 0; i < max_size; ++i) {
        unsigned int digit1 = (i < size_) ? digits_[i] : 0; // Если текущий разряд есть в первом числе, берем его, иначе 0
        unsigned int digit2 = (i < other.size_) ? other.digits_[i] : 0; // Если текущий разряд есть во втором числе, берем его, иначе 0
        temp_sum = digit1 + digit2 + carry;
        result.digits_[i] = static_cast<unsigned char>(temp_sum % 8); // Записываем текущий разряд результата намерено приводя к unsigned char, чтобы не было конфликтов типов
        carry = temp_sum / 8;
    }
    if (carry) {
        result.digits_[max_size] = static_cast<unsigned char>(carry); // Записываем перенос в старший разряд, если он есть, также приводя к unsigned char
        result.size_ = max_size + 1;
    }
    else {
        result.size_ = max_size;
    }
    return result.normalize(); // Возвращаем нормализованный результат, но можно сделать и через цикл while, чтобы лишний раз не копировтаь массив и аллоцировать память
}

// Сравнение
int Octal::compare(const Octal &other) const {
    Octal norm1 = this->normalize();
    Octal norm2 = other.normalize();
    if (norm1.size_ < norm2.size_) return -1;
    if (norm1.size_ > norm2.size_) return 1;
    for (size_t i = norm1.size_; i-- > 0;) { // Идем с конца к началу
        if (norm1.digits_[i] < norm2.digits_[i]) return -1;
        if (norm1.digits_[i] > norm2.digits_[i]) return 1;
    }
    return 0; // Равны
}
bool Octal::equals(const Octal &other) const { return compare(other) == 0; }
bool Octal::less_than(const Octal &other) const { return compare(other) == -1; }

// Вычитание
// Реализуем вычитание слоблбиком, которое подходит почти под все системы счисления
// Если вычитаемое больше уменьшаемого, выбрасываем исключение std::underflow_error, так как ответ будет получаться отрицательным
// Мы создаём новый объект Octal для результата, чтобы не менять текущий объект (так как метод const), начинаем с младшего разряда, пожтому двигаемся с начала
// Если в текущем разряде уменьшаемого меньше, чем в вычитаемом + borrow (заём из старшего разряда), то мы "занимаем" 1 у старшего разряда (добавляем 8 к текущему разряду) и ставим borrow = 1
// Иначе просто вычитаем и ставим borrow = 0
// Разберём на простом примере: 155 - 137
// 1) 5 < 7 + 0, поэтому увеличиваем 5 на 8 (получаем 13), которое уже больше 7 и вычитаем 7, получаем 6, увеличиваем borrow до 1
// 2) 5 > 3 + 1, поэьтому просто вычитаем 4 из 5, получаем 1, borrow = 0
// 3) 1 == 1 + 0, вычитаем 1 - 1 = 0
// В итоге получаем 016, который нормализуем до 16 
Octal Octal::subtract(const Octal &other) const {
    if (this->compare(other) == -1) {
        throw std::underflow_error("Result would be negative");
    }
    Octal result(size_, 0);
    unsigned char borrow = 0;
    for (size_t i = 0; i < size_; ++i) {
        unsigned char digit1 = digits_[i];
        unsigned char digit2 = (i < other.size_) ? other.digits_[i] : 0;
        if (digit1 < digit2 + borrow) {
            result.digits_[i] = static_cast<unsigned char>(digit1 + 8 - digit2 - borrow);
            borrow = 1;
        } else {
            result.digits_[i] = static_cast<unsigned char>(digit1 - digit2 - borrow);
            borrow = 0;
        }
    }
    return result.normalize();
}


std::string Octal::to_string() const {
    std::string result;
    Octal norm = this->normalize();
    for (size_t i = 0; i < norm.size_; ++i) {
        result.push_back(static_cast<char>(norm.digits_[norm.size_ - 1 - i] + '0')); // Преобразование цифр обратно в символы и реверс
    }
    return result;
}