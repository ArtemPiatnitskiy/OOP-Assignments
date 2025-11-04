### Шаблон с параметром-константой

**целочисленную константу (integer constant)**, а не только тип `const int`. 

Параметр `V` в вашем шаблоне называется **нетиповым параметром шаблона (non-type template parameter)**. Для таких параметров в C++ существуют определенные ограничения на типы, которые можно использовать.

В данном случае, `int` — это тип нетипового параметра. При инстанцировании шаблона в качестве аргумента можно передать любое целочисленное константное выражение, например:

```cpp
#include <iostream>

template <int V>
struct foo {    static const int value = V;};

int main() {    foo<10> f1;          // V = 10
    foo<20 + 5> f2;      // V = 25
    const int X = 30;    foo<X> f3;           // V = 30
    // foo<some_variable> f4; // Ошибка: some_variable не константа
        std::cout << f1.value << " " << f2.value << " " << f3.value << std::endl;    return 0;}
```

Используйте код с осторожностью.

Ключевые моменты:

- **Тип параметра (`int`)** определяет, какого типа должна быть константа.
- **Аргумент шаблона** должен быть *константным выражением*, которое может быть вычислено во время компиляции.
- Само ключевое слово `const` в объявлении `static const int value = V;` внутри структуры не имеет прямого отношения к типу *параметра* `V` (он просто `int`), оно лишь определяет свойство *члена данных* `value`.

В современных версиях C++ (начиная с C++20), список допустимых типов для нетиповых параметров шаблонов был расширен и теперь включает литеральные классы, но фундаментальное правило остается: в качестве аргумента должно выступать константное выражение.

### Метафункции (классы-шаблоны)

```c
template<uint64_t n>
struct fact {    static const uint64_t value = fact<n-1>::value * n;};
```

- Вычисления происходят на этапе компиляции
- Использует статические константные поля
- Самый быстрый способ выполнения

## Встроенные концепции C++20

### Числовые концепции

```cpp
std::is_arithmetic_v<T>      // Арифметические типы
std::floating_point<T>       // Типы с плавающей точкой
std::integral<T>             // Целочисленные типы
```

### Концепции равенства и порядка

```cpp
std::equality_comparable<T>   // Поддерживает == и !=
std::totally_ordered<T>      // Поддерживает все операторы сравнения
```

### Другие концепции

```cpp
std::same_as<T, U>           // Типы одинаковы
std::destructible<T>          // Тип может быть разрушен
std::copyable<T>              // Тип может быть скопирован
std::default_constructible<T> // Тип может быть создан по умолчанию
```

### Концепции vs SFINAE

```cpp
// Старый способ (SFINAE)
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
function(T value) { /* ... */ }

// Новый способ (концепции)
template<typename T>
requires std::is_arithmetic_v<T>
void function(T value) { /* ... */ }
```

### Пользовательские концепции

```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
void process(T value) { /* ... */ }
```

### Комбинирование концепций

```cpp
template<typename T>
requires std::is_arithmetic_v<T> && std::copyable<T>
void function(T value) { /* ... */ }
```

# CRTP - Паттерн CRTP (Curiously Recurring Template Pattern)

### Виртуальные функции

```c
class Base {
public:
    virtual void do_action() = 0;  // Виртуальная функция
};

class Child : public Base {
public:
    void do_action() override { /* ... */ }};
```

### CRTP

[](https://github.com/DVDemon/mai_oop_examples_public/tree/main/examples/lection06_07/13_CRTP#crtp)

## Дополнительные возможности

### Множественное наследование с CRTP

```cpp
template <class CHILD>
class Base1 { /* ... */ };

template <class CHILD>
class Base2 { /* ... */ };

class Child : public Base1<Child>, public Base2<Child> {    // ...
};
```

### CRTP с концепциями (C++20)

```cpp
template <class CHILD>
requires std::derived_from<CHILD, Base<CHILD>>
class Base {    // ...
};
```

### Измерение производительности

```cpp
// CRTP - быстрее, нет накладных расходов
// Виртуальные функции - медленнее, есть накладные расходы
```







В C++ такие конструкции, как `std::is_default_constructible<T>`, — это **type traits** (типовые характеристики), то есть шаблонные структуры, которые позволяют на этапе компиляции узнать свойства типа `T`.

Пример:

`std::is_default_constructible<int>`

— это **не** булево значение, а **тип**, у которого есть внутреннее статическое поле `value`.

---

### 📙 Что такое `::value`

`std::is_default_constructible<T>` — это структура, определённая примерно так:

`template <typename T> struct is_default_constructible {    static constexpr bool value = /* true или false */; };`

То есть у неё есть **статическое константное поле `value`**, которое содержит результат проверки (`true` или `false`).

---

### 📗 Почему нужно писать `::value`

Когда ты пишешь:

`std::is_default_constructible<Figure>`

— ты обращаешься к **типу** (структуре), а не к значению.  
Чтобы получить **само значение** (булево `true` или `false`), нужно обратиться к полю:

`std::is_default_constructible<Figure>::value`

Тогда это выражение имеет тип `bool`.

---

### 📘 Пример

`#include <type_traits> #include <iostream>  struct A {};               // имеет конструктор по умолчанию struct B { B(int) {} };    // не имеет конструктора по умолчанию  int main() {     std::cout << std::is_default_constructible<A>::value << "\n"; // 1 (true)     std::cout << std::is_default_constructible<B>::value << "\n"; // 0 (false) }`

---

### 📗 Упрощённый синтаксис

В C++17 и новее можно писать короче, с `_v`:

`std::is_default_constructible_v<Figure>`

Это эквивалентно `std::is_default_constructible<Figure>::value`, просто синтаксический сахар.

---

✅ **Итого:**

| Что написано                                   | Что это значит                   | Тип    |
| ---------------------------------------------- | -------------------------------- | ------ |
| `std::is_default_constructible<Figure>`        | Структура (тип-трейт)            | тип    |
| `std::is_default_constructible<Figure>::value` | Булево значение (`true`/`false`) | `bool` |
| `std::is_default_constructible_v<Figure>`      | Укороченная форма (`C++17+`)     | `bool` |

---

Хочешь, я покажу, как можно использовать это в `concept`, например:

`template<typename T> concept Arrayable = std::is_default_constructible_v<T>;`