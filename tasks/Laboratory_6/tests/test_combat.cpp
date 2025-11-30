#include <gtest/gtest.h>
#include "../include/combat_visitor.h"
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include "../include/file_observer.h"
#include <memory>
#include <fstream>

// Тесты боевой системы
TEST(CombatTest, BearVsBear) {
    CombatVisitor visitor;
    auto bear1 = NpcFactory::createNpc("Bear", "Bear1", 0, 0);
    auto bear2 = NpcFactory::createNpc("Bear", "Bear2", 10, 10);
    
    // Медведь не атакует медведя
    EXPECT_FALSE(visitor.canKill(bear1.get(), bear2.get()));
    EXPECT_FALSE(visitor.canKill(bear2.get(), bear1.get()));
}

TEST(CombatTest, BearVsBittern) {
    CombatVisitor visitor;
    auto bear = NpcFactory::createNpc("Bear", "Bear1", 0, 0);
    auto bittern = NpcFactory::createNpc("Bittern", "Bittern1", 10, 10);
    
    // Медведь ест выпь
    EXPECT_TRUE(visitor.canKill(bear.get(), bittern.get()));
    // Выпь не атакует
    EXPECT_FALSE(visitor.canKill(bittern.get(), bear.get()));
}

TEST(CombatTest, BearVsDesman) {
    CombatVisitor visitor;
    auto bear = NpcFactory::createNpc("Bear", "Bear1", 0, 0);
    auto desman = NpcFactory::createNpc("Desman", "Desman1", 10, 10);
    
    // Медведь ест выхухоль
    EXPECT_TRUE(visitor.canKill(bear.get(), desman.get()));
    // Выхухоль убивает медведя
    EXPECT_TRUE(visitor.canKill(desman.get(), bear.get()));
}

TEST(CombatTest, BitternVsAnyone) {
    CombatVisitor visitor;
    auto bittern = NpcFactory::createNpc("Bittern", "Bittern1", 0, 0);
    auto bear = NpcFactory::createNpc("Bear", "Bear1", 10, 10);
    auto desman = NpcFactory::createNpc("Desman", "Desman1", 20, 20);
    
    // Выпь никого не атакует
    EXPECT_FALSE(visitor.canKill(bittern.get(), bear.get()));
    EXPECT_FALSE(visitor.canKill(bittern.get(), desman.get()));
    EXPECT_FALSE(visitor.canKill(bittern.get(), bittern.get()));
}

TEST(CombatTest, DesmanVsBear) {
    CombatVisitor visitor;
    auto desman = NpcFactory::createNpc("Desman", "Desman1", 0, 0);
    auto bear = NpcFactory::createNpc("Bear", "Bear1", 10, 10);
    
    // Выхухоль убивает медведя
    EXPECT_TRUE(visitor.canKill(desman.get(), bear.get()));
}

TEST(CombatTest, DesmanVsBittern) {
    CombatVisitor visitor;
    auto desman = NpcFactory::createNpc("Desman", "Desman1", 0, 0);
    auto bittern = NpcFactory::createNpc("Bittern", "Bittern1", 10, 10);
    
    // Выхухоль не атакует выпь
    EXPECT_FALSE(visitor.canKill(desman.get(), bittern.get()));
}

TEST(CombatTest, DesmanVsDesman) {
    CombatVisitor visitor;
    auto desman1 = NpcFactory::createNpc("Desman", "Desman1", 0, 0);
    auto desman2 = NpcFactory::createNpc("Desman", "Desman2", 10, 10);
    
    // Выхухоль не атакует выхухоль
    EXPECT_FALSE(visitor.canKill(desman1.get(), desman2.get()));
}

// Тесты боевого режима на арене
TEST(CombatTest, BattleOutOfRange) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // NPC далеко друг от друга
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 0, 0));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 400, 400));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 100 - NPC не достают друг до друга
    arena.startBattle(100.0);
    
    // Оба должны выжить
    EXPECT_EQ(arena.getNpcCount(), 2);
}

TEST(CombatTest, BattleInRange) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Медведь и выпь близко
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 110, 110));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 50 метров
    arena.startBattle(50.0);
    
    // Медведь убивает выпь
    EXPECT_EQ(arena.getNpcCount(), 1);
}

TEST(CombatTest, MutualKill) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Медведь и выхухоль близко
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Desman", "Desman1", 105, 105));
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Дальность боя 50 метров
    arena.startBattle(50.0);
    
    // Оба убивают друг друга
    EXPECT_EQ(arena.getNpcCount(), 0);
}

TEST(CombatTest, ComplexBattle) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Создаём группу NPC
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear2", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 105, 105));
    arena.addNpc(NpcFactory::createNpc("Desman", "Desman1", 115, 115));
    
    EXPECT_EQ(arena.getNpcCount(), 4);
    
    // Запускаем бой с большой дальностью
    arena.startBattle(100.0);
    
    // Медведи убивают выпь, выхухоль убивает медведей, медведи убивают выхухоль
    // Должен остаться 0 или минимум NPC
    EXPECT_LE(arena.getNpcCount(), 2);
}

TEST(CombatTest, BearsSurviveAlone) {
    Arena arena;
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    
    // Только медведи
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear2", 110, 110));
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear3", 120, 120));
    
    EXPECT_EQ(arena.getNpcCount(), 3);
    
    arena.startBattle(100.0);
    
    // Медведи не атакуют друг друга - все выживают
    EXPECT_EQ(arena.getNpcCount(), 3);
}

TEST(CombatTest, FileObserverLogging) {
    std::string logfile = "test_combat_log.txt";
    
    Arena arena;
    auto observer = std::make_shared<FileObserver>(logfile);
    arena.addObserver(observer);
    
    arena.addNpc(NpcFactory::createNpc("Bear", "Bear1", 100, 100));
    arena.addNpc(NpcFactory::createNpc("Bittern", "Bittern1", 110, 110));
    
    arena.startBattle(50.0);
    
    // Проверяем что файл создан
    std::ifstream file(logfile);
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    bool hasContent = false;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            hasContent = true;
            break;
        }
    }
    file.close();
    
    EXPECT_TRUE(hasContent);
    
    // Удаляем тестовый файл
    std::remove(logfile.c_str());
}
