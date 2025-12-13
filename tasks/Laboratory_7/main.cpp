#include "include/arena.h"
#include "include/factory.h"
#include "include/console_observer.h"
#include "include/file_observer.h"
#include <iostream>
#include <memory>

int main() {
    try {
        std::cout << "=== Balagur Fate 3 - Asynchronous Dungeon Battle ===" << std::endl;
        std::cout << std::endl;

        // Создаем арену 100x100
        Arena arena(100, 100);

        // Добавляем наблюдателей
        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>("battle_log.txt");
        
        arena.addObserver(consoleObserver);
        arena.addObserver(fileObserver);

        std::cout << "Генерируем 50 случайных NPC на карте 100x100..." << std::endl;
        arena.generateRandomNpcs(50);
        std::cout << "Создано NPC: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        std::cout << "Параметры NPC:" << std::endl;
        std::cout << "  Bear:    Move=5,  Kill=10" << std::endl;
        std::cout << "  Bittern: Move=50, Kill=10" << std::endl;
        std::cout << "  Desman:  Move=5,  Kill=20" << std::endl;
        std::cout << std::endl;

        std::cout << "Запускаем игру на 30 секунд..." << std::endl;
        std::cout << "Потоки:" << std::endl;
        std::cout << "  1. Поток движения NPC (проверка коллизий)" << std::endl;
        std::cout << "  2. Поток боевой системы (бросок кубиков)" << std::endl;
        std::cout << "  3. Поток вывода карты (каждую секунду)" << std::endl;
        std::cout << std::endl;
        std::cout << "Легенда карты: B=Bear, V=Bittern, D=Desman, .=пусто" << std::endl;
        std::cout << "==========================================================\n" << std::endl;

        // Запускаем игру на 30 секунд
        arena.startGame(30);

        std::cout << "\n==========================================================\n";
        std::cout << "Игра завершена!" << std::endl;
        std::cout << std::endl;

        // Выводим список выживших
        arena.printSurvivors();

        std::cout << "Логи сохранены в файл 'battle_log.txt'" << std::endl;
        std::cout << "=== Программа завершена успешно ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
