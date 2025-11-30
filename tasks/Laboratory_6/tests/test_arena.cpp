#include <gtest/gtest.h>
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include "../include/file_observer.h"
#include <memory>
#include <fstream>
#include <sstream>

// Тесты арены
TEST(ArenaTest, CreateArena) {
    Arena arena(500, 500);
    EXPECT_EQ(arena.getNpcCount(), 0);
}

TEST(ArenaTest, CreateArenaInvalidSize) {
    EXPECT_THROW({
        Arena arena(600, 600);  // Больше максимума
    }, std::out_of_range);
}

TEST(ArenaTest, AddNpc) {
    Arena arena;
    auto bear = NpcFactory::createNpc("Bear", "Mishka", 100, 100);
    arena.addNpc(std::move(bear));
    
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(ArenaTest, AddMultipleNpcs) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 200, 200));
    arena.addNpc(NpcFactory::createNpc("Desman", "Desman1", 300, 300));
    
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(ArenaTest, AddNpcDuplicateName) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Bear", "Duplicate", 100, 100));
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Desman", "Duplicate", 200, 200));
    }, std::invalid_argument);
}

TEST(ArenaTest, AddNpcOutOfBounds) {
    Arena arena(500, 500);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Bear", "OutBear", 600, 100));
    }, std::out_of_range);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Bear", "OutBear2", 100, 600));
    }, std::out_of_range);
    
    EXPECT_THROW({
        arena.addNpc(NpcFactory::createNpc("Bear", "NegativeBear", -10, 100));
    }, std::out_of_range);
}

TEST(ArenaTest, ClearArena) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 200, 200));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    arena.clear();
    EXPECT_EQ(arena.getNpcCount(), 0);
}

// Тесты сохранения/загрузки
TEST(ArenaTest, SaveToFile) {
    Arena arena;
    
    arena.addNpc(NpcFactory::createNpc("Bear", "Mishka", 100, 200));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Vypochka", 150, 250));
    arena.addNpc(NpcFactory::createNpc("Desman", "Vyhuhol", 50, 75));
    
    std::string filename = "test_save.txt";
    arena.saveToFile(filename);
    
    // Проверяем, что файл создан и содержит данные
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    file.close();
    
    EXPECT_EQ(lineCount, 3);
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST(ArenaTest, LoadFromFile) {
    // Создаём тестовый файл
    std::string filename = "test_load.txt";
    std::ofstream outfile(filename);
    outfile << "Bear Mishka 100 200\n";
    outfile << "Bittern Vypochka 150 250\n";
    outfile << "Desman Vyhuhol 50 75\n";
    outfile.close();
    
    // Загружаем из файла
    Arena arena;
    arena.loadFromFile(filename);
    
    EXPECT_EQ(arena.getNpcCount(), 3);
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST(ArenaTest, LoadFromNonExistentFile) {
    Arena arena;
    
    EXPECT_THROW({
        arena.loadFromFile("nonexistent_file.txt");
    }, std::runtime_error);
}

TEST(ArenaTest, SaveAndLoadRoundtrip) {
    std::string filename = "test_roundtrip.txt";
    
    // Создаём арену и добавляем NPC
    {
        Arena arena1;
        arena1.addNpc(NpcFactory::createNpc("Bear", "Bear1", 111, 222));
        arena1.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 333, 444));
        arena1.saveToFile(filename);
    }
    
    // Загружаем в новую арену
    {
        Arena arena2;
        arena2.loadFromFile(filename);
        EXPECT_EQ(arena2.getNpcCount(), 2);
    }
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

// Тесты Observer
TEST(ArenaTest, AddObserver) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    
    EXPECT_NO_THROW({
        arena.addObserver(observer);
    });
}

TEST(ArenaTest, AddFileObserver) {
    Arena arena;
    auto observer = std::make_shared<FileObserver>("test_observer.txt");
    
    EXPECT_NO_THROW({
        arena.addObserver(observer);
    });
    
    // Удаляем тестовый файл если создался
    std::remove("test_observer.txt");
}
