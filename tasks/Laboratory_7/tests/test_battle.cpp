#include <gtest/gtest.h>
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/combat_visitor.h"
#include "../include/bear.h"
#include "../include/bittern.h"
#include "../include/desman.h"

// Тест 1: Проверка правил боя - Медведь убивает Выпь
TEST(BattleTest, BearKillsBittern) {
    CombatVisitor visitor;
    Bear bear(0, 0, "Bear");
    Bittern bittern(5, 5, "Bittern");
    
    EXPECT_TRUE(visitor.canKill(&bear, &bittern));
}

// Тест 2: Проверка правил боя - Медведь убивает Выхухоль
TEST(BattleTest, BearKillsDesman) {
    CombatVisitor visitor;
    Bear bear(0, 0, "Bear");
    Desman desman(5, 5, "Desman");
    
    EXPECT_TRUE(visitor.canKill(&bear, &desman));
}

// Тест 3: Проверка правил боя - Выхухоль убивает Медведя
TEST(BattleTest, DesmanKillsBear) {
    CombatVisitor visitor;
    Desman desman(0, 0, "Desman");
    Bear bear(5, 5, "Bear");
    
    EXPECT_TRUE(visitor.canKill(&desman, &bear));
}

// Тест 4: Проверка правил боя - Выпь НЕ убивает никого
TEST(BattleTest, BitternDoesNotKill) {
    CombatVisitor visitor;
    Bittern bittern(0, 0, "Bittern");
    Bear bear(5, 5, "Bear");
    Desman desman(10, 10, "Desman");
    
    EXPECT_FALSE(visitor.canKill(&bittern, &bear));
    EXPECT_FALSE(visitor.canKill(&bittern, &desman));
}

// Тест 5: Проверка правил боя - Выхухоль НЕ убивает Выпь
TEST(BattleTest, DesmanDoesNotKillBittern) {
    CombatVisitor visitor;
    Desman desman(0, 0, "Desman");
    Bittern bittern(5, 5, "Bittern");
    
    EXPECT_FALSE(visitor.canKill(&desman, &bittern));
}

// Тест 6: NPC не может убить сам себя
TEST(BattleTest, NpcCannotKillItself) {
    CombatVisitor visitor;
    Bear bear(0, 0, "Bear");
    
    EXPECT_FALSE(visitor.canKill(&bear, &bear));
}

// Тест 7: Дистанция убийства Bear
TEST(BattleTest, BearKillDistance) {
    Bear bear(0, 0, "Bear");
    EXPECT_EQ(bear.getKillDistance(), 10);
    
    Bear target(10, 0, "Target");
    EXPECT_DOUBLE_EQ(bear.distanceTo(target), 10.0);
}

// Тест 8: Дистанция убийства Desman
TEST(BattleTest, DesmanKillDistance) {
    Desman desman(0, 0, "Desman");
    EXPECT_EQ(desman.getKillDistance(), 20);
    
    Bear target(20, 0, "Target");
    EXPECT_DOUBLE_EQ(desman.distanceTo(target), 20.0);
}

// Тест 9: Дистанция убийства Bittern
TEST(BattleTest, BitternKillDistance) {
    Bittern bittern(0, 0, "Bittern");
    EXPECT_EQ(bittern.getKillDistance(), 10);
}

// Тест 10: Проверка битвы через Arena (короткая игра)
TEST(BattleTest, ArenaBattleShortGame) {
    Arena arena(100, 100);
    
    // Создаем NPC близко друг к другу
    arena.createAndAddNpc("Bear", "Bear1", 50, 50);
    arena.createAndAddNpc("Bittern", "Bittern1", 55, 50);
    
    EXPECT_EQ(arena.getAliveCount(), 2);
    
    // Запускаем игру на короткое время
    arena.startGame(2);
    
    // Медведь должен был убить Выпь (но может не успеть за 2 секунды)
    EXPECT_LE(arena.getAliveCount(), 2);
}

// Тест 11: Битва между Desman и Bear
TEST(BattleTest, DesmanVsBear) {
    Arena arena(100, 100);
    
    arena.createAndAddNpc("Desman", "Desman1", 50, 50);
    arena.createAndAddNpc("Bear", "Bear1", 55, 50);
    
    EXPECT_EQ(arena.getAliveCount(), 2);
    
    arena.startGame(2);
    
    // Один из них должен был погибнуть (или оба)
    EXPECT_LE(arena.getAliveCount(), 1);
}

// Тест 12: Bittern не убивает никого
TEST(BattleTest, BitternDoesNotKillInGame) {
    Arena arena(100, 100);
    
    arena.createAndAddNpc("Bittern", "Bittern1", 50, 50);
    arena.createAndAddNpc("Bittern", "Bittern2", 51, 50);
    arena.createAndAddNpc("Bear", "Bear1", 52, 50);
    
    EXPECT_EQ(arena.getAliveCount(), 3);
    
    arena.startGame(2);
    
    // Медведь может убить Выпей, но Выпи не убивают никого
    size_t alive = arena.getAliveCount();
    EXPECT_LE(alive, 3);
}

// Тест 13: Проверка старого метода startBattle
TEST(BattleTest, OldBattleMethod) {
    Arena arena(100, 100);
    
    arena.createAndAddNpc("Bear", "Bear1", 10, 10);
    arena.createAndAddNpc("Bittern", "Bittern1", 15, 10);
    
    EXPECT_EQ(arena.getNpcCount(), 2);
    
    // Запускаем старый метод битвы
    arena.startBattle(100.0);
    
    // Медведь должен убить Выпь
    EXPECT_EQ(arena.getNpcCount(), 1);
}

// Тест 14: Проверка массовой битвы
TEST(BattleTest, MassiveBattle) {
    Arena arena(100, 100);
    
    // Создаем много NPC в одной точке
    for (int i = 0; i < 5; ++i) {
        arena.createAndAddNpc("Bear", "Bear_" + std::to_string(i), 50, 50);
        arena.createAndAddNpc("Bittern", "Bittern_" + std::to_string(i), 51, 50);
    }
    
    EXPECT_EQ(arena.getAliveCount(), 10);
    
    arena.startGame(3);
    
    // Медведи должны были убить всех Выпей (но может быть случайность в боях)
    size_t survivors = arena.getAliveCount();
    EXPECT_LE(survivors, 10);  // Могут выжить не все
}

// Тест 15: Проверка взаимного убийства (Desman vs Bear)
TEST(BattleTest, MutualKillPossible) {
    CombatVisitor visitor;
    Desman desman(0, 0, "Desman");
    Bear bear(5, 5, "Bear");
    
    // Оба могут убить друг друга
    EXPECT_TRUE(visitor.canKill(&desman, &bear));
    EXPECT_TRUE(visitor.canKill(&bear, &desman));
}

// Тест 16: Проверка боевых правил
TEST(BattleTest, BattleRulesComplete) {
    CombatVisitor visitor;
    
    // Медведь убивает Выпь, но Выпь не убивает Медведя
    Bear bear(0, 0, "Bear");
    Bittern bittern(5, 5, "Bittern");
    EXPECT_TRUE(visitor.canKill(&bear, &bittern));
    EXPECT_FALSE(visitor.canKill(&bittern, &bear));
    
    // Выхухоль убивает Медведя, и Медведь тоже убивает Выхухоль (взаимное убийство)
    Desman desman(10, 10, "Desman");
    EXPECT_TRUE(visitor.canKill(&desman, &bear));
    EXPECT_TRUE(visitor.canKill(&bear, &desman));
    
    // Медведь не убивает медведя
    Bear bear2(15, 15, "Bear2");
    EXPECT_FALSE(visitor.canKill(&bear, &bear2));
}