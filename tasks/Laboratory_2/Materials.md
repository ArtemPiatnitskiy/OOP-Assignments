# #include algorithm - Что это и для чего?

Библиотека `<algorithm>` — это заголовочный файл в стандартной библиотеке C++, который содержит набор функций для выполнения различных операций над диапазонами элементов. Эти операции включают в себя поиск, сортировку, преобразование, копирование и другие алгоритмы, которые часто используются при работе с данными.

**Что она из себя представляет:**

- **Набор алгоритмов:** `<algorithm>` предоставляет широкий спектр готовых к использованию алгоритмов.
- **Обобщенное программирование:** Алгоритмы в `<algorithm>` написаны с использованием шаблонов, что позволяет им работать с различными типами данных и контейнеров.
- **Эффективность:** Многие алгоритмы реализованы с высокой степенью оптимизации, что обеспечивает хорошую производительность.
- **Удобство:** Использование алгоритмов из `<algorithm>` может значительно упростить код и сделать его более читаемым.

**Как она устроена:**

Большинство алгоритмов в `<algorithm>` принимают итераторы в качестве аргументов. Итераторы указывают на начало и конец диапазона элементов, над которым нужно выполнить операцию. Алгоритмы работают с элементами в этом диапазоне, используя итераторы для доступа к ним.

**Что она делает:**

Библиотека `<algorithm>` предоставляет функции для:

- **Поиска:** `find`, `find_if`, `binary_search` и другие алгоритмы для поиска элементов в диапазоне.
- **Сортировки:** `sort`, `partial_sort`, `stable_sort` и другие алгоритмы для сортировки элементов в диапазоне.
- **Преобразования:** `transform`, `replace`, `remove` и другие алгоритмы для преобразования элементов в диапазоне.
- **Копирования:** `copy`, `copy_if`, `unique_copy` и другие алгоритмы для копирования элементов из одного диапазона в другой.
- **Математических операций:** `accumulate`, `inner_product` и другие алгоритмы для выполнения математических операций над элементами в диапазоне.
- **Других операций:** `for_each`, `count`, `min`, `max` и другие алгоритмы для выполнения различных других операций над элементами в диапазоне.

**Когда её нужно использовать:**

Использовать библиотеку `<algorithm>`, нужно когда мы хотим выполнить какую-либо операцию над диапазоном элементов, такую как поиск, сортировка, преобразование или копирование. Использование алгоритмов из `<algorithm>` может значительно упростить код и сделать его более читаемым и эффективным.

К примеру, если нам нужно отсортировать вектор чисел:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 4};

    std::sort(numbers.begin(), numbers.end());

    for (int number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

В этом примере алгоритм `std::sort` сортирует элементы вектора `numbers` по возрастанию.

## **1. `max` и `min`**

- **Прототипы:**
  
  ```cpp
  template <typename T>
  const T& max(const T& a, const T& b);
  
  template <typename T>
  const T& min(const T& a, const T& b);
  ```

- **Что принимают:**
  
  - `a`: Первый аргумент для сравнения (типа `T`).
  - `b`: Второй аргумент для сравнения (типа `T`).

- **Что делают "под капотом":**
  
  - `max`: Сравнивает `a` и `b` с помощью оператора `<` (или пользовательской функции сравнения, если она предоставлена). Возвращает ссылку на больший из двух аргументов.
  - `min`: Сравнивает `a` и `b` с помощью оператора `<` (или пользовательской функции сравнения, если она предоставлена). Возвращает ссылку на меньший из двух аргументов.

```cpp
#include <iostream>
#include <algorithm>

int main() {
    int a = 10;
    int b = 20;

    int maximum = std::max(a, b);
    int minimum = std::min(a, b);

    std::cout << "Max: " << maximum << std::endl; // Вывод: Max: 20
    std::cout << "Min: " << minimum << std::endl;   // Вывод: Min: 10

    return 0;
}
```

Данную функцию не сложно реализовать самостоятельно:

```cpp
int myMax(int a, int b) {
    return (a > b) ? a : b;
}

int myMin(int a, int b) {
    return (a < b) ? a : b;
}
```

В данном примере функция реализована для 1 типа, чтобы сделать её для разных типов, используются шаблоны

## **2. `fill`**

**Прототип:**

```cpp
template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value);
```

- **Что принимает:**
  
  - `first`: Итератор, указывающий на начало диапазона.
  - `last`: Итератор, указывающий на конец диапазона.
  - `value`: Значение, которым нужно заполнить диапазон.

- **то делает "под капотом":**
  
  - Присваивает значение `value` каждому элементу в диапазоне `[first, last)`.

- **Пример использования:**
  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>
  
  int main() {
      std::vector<int> data(5);
  
      std::fill(data.begin(), data.end(), 100);
  
      for (int value : data) {
          std::cout << value << " "; // Вывод: 100 100 100 100 100
      }
      std::cout << std::endl;
  
      return 0;
  }
  ```

- Ручная реализация для `int`
  
  ```cpp
  void myFill(int* first, int* last, int value) {
      for (int* it = first; it != last; ++it) {
          *it = value;
      }
  }
  ```

## **3. `copy`**

- **Прототип:**
  
  ```cpp
  template <typename InputIterator, typename OutputIterator>
  OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);
  ```

- **Что принимает:**
  
  - `first`: Итератор, указывающий на начало диапазона, который нужно скопировать.
  - `last`: Итератор, указывающий на конец диапазона, который нужно скопировать.
  - `result`: Итератор, указывающий на начало диапазона, в который нужно скопировать элементы.

- **Что делает "под капотом":**
  
  - Копирует элементы из диапазона `[first, last)` в диапазон, начинающийся с `result`. Возвращает итератор, указывающий на конец скопированного диапазона в `result`.

- **Пример использования:**
  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>
  
  int main() {
      std::vector<int> source = {1, 2, 3, 4, 5};
      std::vector<int> destination(5);
  
      std::copy(source.begin(), source.end(), destination.begin());
  
      for (int value : destination) {
          std::cout << value << " "; // Вывод: 1 2 3 4 5
      }
      std::cout << std::endl;
  
      return 0;
  }
  ```

- **Ручная реализация для `int`:**
  
  ```cpp
  void myCopy(const unsigned char* first, const unsigned char* last, unsigned char* result) {
      for (const unsigned char* it = first; it != last; ++it, ++result) {
          *result = *it;
      }
  }
  ```

**Пример использования из реализации ЛР:**

```cpp
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
```

Представим, что у нас есть массив из 5 элементов:

```
digits_ -> [_, _, _, _, _]
            ^           ^
            |           |
          digits_      digits_ + size_ (где size_ = 5)
```

`std::fill(digits_, digits_ + size_, fill)` заполнит все 5 элементов массива значением `fill`.

Если бы мы написали `std::fill(digits_, digits_ + size_ - 1, fill)`, то заполнились бы только первые 4 элемента, а последний остался бы нетронутым. Это было бы неправильно, так как мы хотим инициализировать *весь* массив.



 

# Функция normolize

Если у нас есть число вида "1235000", то мы должны преобразовать его в "1235", чтобы отбросить нули, которые нам не нужны

Вариант, который используется в ЛР иммутабельный (согласно условию) - значит функция должна вернуть новый объект. Данный подход расходует память и не оптимизирован, поэтому  лучше использовать другой способ.

Вместо того, чтобы возвращать новый объект, мы будем менять исходный:

```cpp
void Octal::normalize(){
    // Размер 0 не допускается - должен быть минимуим 1
    if (size_ == 0) {
        size_ = 1;
        delete[] digits_;
        digits_ = new unsigned char[1]{0};
    }
    // Удаление ведущих нулей
    size_t new_size = size_;
    while (new_size > 1 && digits_[new_size - 1] == 0) --new_size;

    if (new_size != size_) {
        unsigned char *new_digits = new unsigned char[new_size];
        std::copy(digits_, digits_ + new_size, new_digits);
        delete[] digits_;
        digits_ = new_digits;
        size_ = new_size;
    }
}
```
