#include "include/arena.h"
#include "include/factory.h"
#include "include/console_observer.h"
#include "include/file_observer.h"
#include <iostream>
#include <memory>

int main() {
    try {
        std::cout << "=== Тест загрузки из файла ===" << std::endl;
        std::cout << std::endl;

        // Создаём арену
        Arena arena(500, 500);

        // Добавляем наблюдателей
        auto consoleObserver = std::make_shared<ConsoleObserver>();
        auto fileObserver = std::make_shared<FileObserver>("battle_log.txt");
        
        arena.addObserver(consoleObserver);
        arena.addObserver(fileObserver);

        // Загружаем NPC из файла
        std::cout << "1. Загружаем NPC из файла 'test_npcs.txt'..." << std::endl;
        arena.loadFromFile("test_npcs.txt");
        std::cout << "Загружено NPC: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        // Показываем всех NPC
        std::cout << "2. Список загруженных NPC:" << std::endl;
        arena.printAllNpcs();
        std::cout << std::endl;

        // Запускаем бой с разными дальностями
        std::cout << "3. Запускаем бой с дальностью 50 метров..." << std::endl;
        std::cout << "--- НАЧАЛО БОЯ ---" << std::endl;
        arena.startBattle(50.0);
        std::cout << "--- КОНЕЦ БОЯ ---" << std::endl;
        std::cout << std::endl;

        // Показываем выживших
        std::cout << "4. Выжившие после боя:" << std::endl;
        arena.printAllNpcs();
        std::cout << "Осталось NPC: " << arena.getNpcCount() << std::endl;
        std::cout << std::endl;

        // Сохраняем результат
        std::cout << "5. Сохраняем выживших в 'survivors.txt'..." << std::endl;
        arena.saveToFile("survivors.txt");
        std::cout << "Сохранено!" << std::endl;
        std::cout << std::endl;

        std::cout << "=== Тест завершён успешно ===" << std::endl;
        std::cout << "Проверьте файл 'battle_log.txt' для просмотра событий боя." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
