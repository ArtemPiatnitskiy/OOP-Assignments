// #include "include/fixed_block_memory_resource.h"
// #include "include/doubly_linked_list.h"
// #include <iostream>
// #include <string>
// #include <algorithm>
// #include <numeric>

// // Структура для демонстрации работы со сложным типом
// struct Person {
//     std::string name;
//     int age;
//     double salary;
    
//     Person(const std::string& n, int a, double s)
//         : name(n), age(a), salary(s) {}
    
//     friend std::ostream& operator<<(std::ostream& os, const Person& p) {
//         os << "Person{name: " << p.name << ", age: " << p.age 
//            << ", salary: $" << p.salary << "}";
//         return os;
//     }
// };

// void print_separator(const std::string& title) {
//     std::cout << "\n" << std::string(50, '=') << "\n";
//     std::cout << title << "\n";
//     std::cout << std::string(50, '=') << "\n";
// }

// void demo_simple_types() {
//     print_separator("ДЕМОНСТРАЦИЯ С ПРОСТЫМИ ТИПАМИ (int)");
    
//     // Создаём memory_resource с пулом 4KB
//     fixed_block_memory_resource mr(4096);
    
//     std::cout << "Создан memory_resource с пулом: " << mr.get_free_memory() << " байт\n\n";
    
//     // Создаём список целых чисел
//     doubly_linked_list<int> numbers(&mr);
    
//     std::cout << "Добавляем элементы через push_back...\n";
//     for (int i = 1; i <= 5; ++i) {
//         numbers.push_back(i * 10);
//         std::cout << "  Добавлен: " << i * 10 << "\n";
//     }
    
//     std::cout << "\nДобавляем элементы через push_front...\n";
//     for (int i = 1; i <= 3; ++i) {
//         numbers.push_front(i);
//         std::cout << "  Добавлен в начало: " << i << "\n";
//     }
    
//     std::cout << "\nРазмер списка: " << numbers.size() << "\n";
//     std::cout << "Использовано памяти: " << mr.get_used_memory() << " байт\n";
//     std::cout << "Свободно памяти: " << mr.get_free_memory() << " байт\n";
    
//     std::cout << "\nСодержимое списка (через итератор):\n";
//     std::cout << "  ";
//     for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << "\n";
    
//     std::cout << "\nСодержимое списка (range-based for):\n";
//     std::cout << "  ";
//     for (int value : numbers) {
//         std::cout << value << " ";
//     }
//     std::cout << "\n";
    
//     std::cout << "\nУдаляем 2 элемента с конца...\n";
//     numbers.pop_back();
//     numbers.pop_back();
//     std::cout << "Размер списка: " << numbers.size() << "\n";
    
//     std::cout << "\nУдаляем 1 элемент с начала...\n";
//     numbers.pop_front();
//     std::cout << "Размер списка: " << numbers.size() << "\n";
    
//     std::cout << "\nСодержимое после удаления:\n";
//     std::cout << "  ";
//     numbers.print_list();
    
//     std::cout << "\nОчищаем список...\n";
//     numbers.clear();
//     std::cout << "Список пуст: " << (numbers.empty() ? "Да" : "Нет") << "\n";
//     std::cout << "Размер: " << numbers.size() << "\n";
    
//     // Проверка переиспользования памяти
//     std::cout << "\nДобавляем элементы снова (память должна переиспользоваться)...\n";
//     size_t used_before = mr.get_used_memory();
//     for (int i = 100; i <= 105; ++i) {
//         numbers.push_back(i);
//     }
//     size_t used_after = mr.get_used_memory();
    
//     std::cout << "Память до: " << used_before << " байт\n";
//     std::cout << "Память после: " << used_after << " байт\n";
//     std::cout << "Разница: " << (used_after - used_before) << " байт (должна быть небольшой)\n";
    
//     std::cout << "\nСодержимое:\n";
//     std::cout << "  ";
//     numbers.print_list();
// }

// void demo_complex_types() {
//     print_separator("ДЕМОНСТРАЦИЯ СО СЛОЖНЫМИ ТИПАМИ (struct Person)");
    
//     // Создаём memory_resource с пулом 8KB
//     fixed_block_memory_resource mr(8192);
    
//     std::cout << "Создан memory_resource с пулом: " << mr.get_free_memory() << " байт\n\n";
    
//     // Создаём список людей
//     doubly_linked_list<Person> people(&mr);
    
//     std::cout << "Добавляем сотрудников...\n";
//     people.push_back(Person("Alice Johnson", 28, 75000.0));
//     people.push_back(Person("Bob Smith", 35, 92000.0));
//     people.push_back(Person("Charlie Brown", 42, 105000.0));
//     people.push_back(Person("Diana Prince", 31, 88000.0));
    
//     std::cout << "Добавлено " << people.size() << " сотрудников\n";
//     std::cout << "Использовано памяти: " << mr.get_used_memory() << " байт\n\n";
    
//     std::cout << "Список сотрудников:\n";
//     int index = 1;
//     for (const auto& person : people) {
//         std::cout << "  " << index++ << ". " << person << "\n";
//     }
    
//     std::cout << "\nИспользуем оператор стрелки (->):\n";
//     auto it = people.begin();
//     std::cout << "  Первый сотрудник: " << it->name << ", возраст: " << it->age << "\n";
//     ++it;
//     std::cout << "  Второй сотрудник: " << it->name << ", зарплата: $" << it->salary << "\n";
    
//     std::cout << "\nПовышаем зарплату всем на 10%...\n";
//     for (auto& person : people) {
//         person.salary *= 1.1;
//     }
    
//     std::cout << "\nОбновлённый список:\n";
//     index = 1;
//     for (const auto& person : people) {
//         std::cout << "  " << index++ << ". " << person << "\n";
//     }
    
//     std::cout << "\nВычисляем среднюю зарплату...\n";
//     double total_salary = 0.0;
//     for (const auto& person : people) {
//         total_salary += person.salary;
//     }
//     double average = total_salary / people.size();
//     std::cout << "  Средняя зарплата: $" << average << "\n";
    
//     std::cout << "\nУдаляем последнего сотрудника...\n";
//     people.pop_back();
//     std::cout << "Осталось сотрудников: " << people.size() << "\n";
    
//     std::cout << "\nФинальный список:\n";
//     index = 1;
//     for (const auto& person : people) {
//         std::cout << "  " << index++ << ". " << person << "\n";
//     }
// }

// void demo_memory_stats() {
//     print_separator("СТАТИСТИКА ИСПОЛЬЗОВАНИЯ ПАМЯТИ");
    
//     fixed_block_memory_resource mr(2048);
//     doubly_linked_list<int> list(&mr);
    
//     std::cout << "Начальное состояние:\n";
//     std::cout << "  Свободно: " << mr.get_free_memory() << " байт\n";
//     std::cout << "  Использовано: " << mr.get_used_memory() << " байт\n\n";
    
//     std::cout << "Добавляем 10 элементов...\n";
//     for (int i = 0; i < 10; ++i) {
//         list.push_back(i);
//     }
    
//     std::cout << "После добавления:\n";
//     std::cout << "  Свободно: " << mr.get_free_memory() << " байт\n";
//     std::cout << "  Использовано: " << mr.get_used_memory() << " байт\n";
//     std::cout << "  Размер списка: " << list.size() << " элементов\n\n";
    
//     std::cout << "Информация о выделенных блоках:\n";
//     mr.print_allocated_blocks();
    
//     std::cout << "\nОчищаем список...\n";
//     list.clear();
    
//     std::cout << "После очистки:\n";
//     std::cout << "  Размер списка: " << list.size() << " элементов\n";
//     std::cout << "  Использовано памяти: " << mr.get_used_memory() << " байт (память НЕ возвращена в систему)\n\n";
    
//     std::cout << "Информация о блоках (помечены как свободные):\n";
//     mr.print_allocated_blocks();
    
//     std::cout << "\nДобавляем 5 элементов (переиспользование памяти)...\n";
//     for (int i = 100; i < 105; ++i) {
//         list.push_back(i);
//     }
    
//     std::cout << "После переиспользования:\n";
//     std::cout << "  Использовано: " << mr.get_used_memory() << " байт\n";
//     std::cout << "  Размер списка: " << list.size() << " элементов\n\n";
    
//     std::cout << "Информация о блоках:\n";
//     mr.print_allocated_blocks();
// }

// void demo_iterator_algorithms() {
//     print_separator("ИСПОЛЬЗОВАНИЕ ИТЕРАТОРОВ С STL АЛГОРИТМАМИ");
    
//     fixed_block_memory_resource mr(4096);
//     doubly_linked_list<int> numbers(&mr);
    
//     // Заполняем список
//     for (int i = 1; i <= 10; ++i) {
//         numbers.push_back(i);
//     }
    
//     std::cout << "Исходный список:\n  ";
//     numbers.print_list();
    
//     // std::find
//     std::cout << "\nПоиск числа 7 (std::find):\n";
//     auto found = std::find(numbers.begin(), numbers.end(), 7);
//     if (found != numbers.end()) {
//         std::cout << "  Найдено: " << *found << "\n";
//     }
    
//     // std::count
//     numbers.push_back(5); // Добавляем дубликат
//     numbers.push_back(5);
//     std::cout << "\nКоличество пятёрок (std::count): " 
//               << std::count(numbers.begin(), numbers.end(), 5) << "\n";
    
//     // std::accumulate
//     int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
//     std::cout << "\nСумма всех элементов (std::accumulate): " << sum << "\n";
    
//     // std::distance
//     auto distance = std::distance(numbers.begin(), numbers.end());
//     std::cout << "\nРасстояние от begin до end (std::distance): " << distance << "\n";
//     std::cout << "Размер списка (size()): " << numbers.size() << "\n";
// }

// int main() {
//     std::cout << "\n";
//     std::cout << "╔════════════════════════════════════════════════════╗\n";
//     std::cout << "║   ЛАБОРАТОРНАЯ РАБОТА №5                          ║\n";
//     std::cout << "║   Итераторы и аллокаторы                          ║\n";
//     std::cout << "║   Двунаправленный список с custom memory_resource ║\n";
//     std::cout << "╚════════════════════════════════════════════════════╝\n";
    
//     try {
//         demo_simple_types();
//         demo_complex_types();
//         demo_memory_stats();
//         demo_iterator_algorithms();
        
//         print_separator("ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА УСПЕШНО");
//         std::cout << "\nВсе операции выполнены без ошибок!\n\n";
        
//     } catch (const std::exception& e) {
//         std::cerr << "\n[ОШИБКА] " << e.what() << "\n";
//         return 1;
//     }
    
//     return 0;
// }


#include "include/fixed_block_memory_resource.h"
#include "include/doubly_linked_list.h"
#include <iostream>
#include <string>
#include <chrono>
#include <list>

struct color {
    std::string name;
    int r, g, b;

    color(const std::string& n, int red, int green, int blue)
        : name(n), r(red), g(green), b(blue) {}
};


void test_standard_allocator() {
    std::cout << "Test standard allocator\n";

    auto start_time = std::chrono::high_resolution_clock::now();

    std::list<color> standard_list;

    const int TEST_SIZE = 50000; // Уменьшаем для сопоставимости
    
    for (int i = 0; i < TEST_SIZE; ++i) {
        standard_list.push_back(color("Color" + std::to_string(i), i, i, i));
    }

    for (int i = 0; i < TEST_SIZE; ++i) {
        standard_list.erase(standard_list.begin());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Standard allocator time: " << duration << " ms (tested with " << TEST_SIZE << " elements)\n";

}

void test_custom_allocator() {
    std::cout << "Test custom allocator\n";

    auto start_time = std::chrono::high_resolution_clock::now();

    // Увеличиваем пул до 512 MB (строки занимают много места!)
    fixed_block_memory_resource mr(1024ULL * 1024 * 512);
    doubly_linked_list<color> custom_list(&mr);

    const int TEST_SIZE = 50000; // Уменьшаем до 50k для разумного времени теста
    
    for (int i = 0; i < TEST_SIZE; ++i) {
        custom_list.push_back(color("Color" + std::to_string(i), i, i, i));
    }

    for (int i = 0; i < TEST_SIZE; ++i) {
        custom_list.pop_front();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Custom allocator time: " << duration << " ms (tested with " << TEST_SIZE << " elements)\n";

}

int main() {
    fixed_block_memory_resource mr(4096);

       
    
    doubly_linked_list<int> list(&mr);
    
    list.push_back(10);
    list.pop_back();
    
    mr.print_allocated_blocks();
    
    std::cout << "\n==============================================\n";
    
    doubly_linked_list<color> colors(&mr);

    colors.push_back(color("Red", 255, 0, 0));
    colors.push_back(color("Green", 0, 255, 0));
    colors.push_back(color("Blue", 0, 0, 255));
    colors.push_back(color("White", 255, 255, 255));
    colors.push_back(color("Black", 0, 0, 0));

    std::cout << "Colors in the list:\n";
    for (const auto& col : colors) {
        std::cout << "  " << col.name << " (RGB: " << col.r << ", " << col.g << ", " << col.b << ")\n";
    }

    // Без фигурных/без круглых скобок это объявление функции (most-vexing-parse).
    // Создаём объект с дефолтным конструктором:
    fixed_block_memory_resource mr_2{};

    std::cout << "\n==============================================\n";

    mr_2.print_allocated_blocks();

    doubly_linked_list<void*> list_2(&mr_2);

    for (int i = 0; i < 100; ++i) {
        list_2.push_back((void*)new color("Color" + std::to_string(i), i, i, i));
        list_2.push_back((void*)new int(i));
    }

    std::cout << "\nList 2 contents:\n";

    list_2.print_list();

    std::cout << "\n==============================================\n";

    mr_2.print_allocated_blocks();
    
    std::cout << "\n==============================================\n";

    list_2.clear();
    mr_2.print_allocated_blocks();

    test_standard_allocator();
    test_custom_allocator();


    return 0;
}