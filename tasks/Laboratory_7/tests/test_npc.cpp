#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/bear.h"
#include "../include/bittern.h"
#include "../include/desman.h"
#include <thread>
#include <vector>

// Тест 1: Проверка создания NPC
TEST(NpcTest, CreateNpc) {
    Bear bear(10, 20, "Mishka");
    EXPECT_EQ(bear.getX(), 10);
    EXPECT_EQ(bear.getY(), 20);
    EXPECT_EQ(bear.getName(), "Mishka");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_TRUE(bear.isAlive());
}

// Тест 2: Проверка параметров движения Bear
TEST(NpcTest, BearMovementParameters) {
    Bear bear(0, 0, "TestBear");
    EXPECT_EQ(bear.getMoveDistance(), 5);
    EXPECT_EQ(bear.getKillDistance(), 10);
}

// Тест 3: Проверка параметров движения Bittern
TEST(NpcTest, BitternMovementParameters) {
    Bittern bittern(0, 0, "TestBittern");
    EXPECT_EQ(bittern.getMoveDistance(), 50);
    EXPECT_EQ(bittern.getKillDistance(), 10);
}

// Тест 4: Проверка параметров движения Desman
TEST(NpcTest, DesmanMovementParameters) {
    Desman desman(0, 0, "TestDesman");
    EXPECT_EQ(desman.getMoveDistance(), 5);
    EXPECT_EQ(desman.getKillDistance(), 20);
}

// Тест 5: Проверка расчета расстояния
TEST(NpcTest, DistanceCalculation) {
    Bear bear1(0, 0, "Bear1");
    Bear bear2(3, 4, "Bear2");
    EXPECT_DOUBLE_EQ(bear1.distanceTo(bear2), 5.0);
}

// Тест 6: Проверка изменения позиции
TEST(NpcTest, SetPosition) {
    Bear bear(10, 20, "Mishka");
    bear.setPosition(30, 40);
    EXPECT_EQ(bear.getX(), 30);
    EXPECT_EQ(bear.getY(), 40);
}

// Тест 7: Проверка setX и setY
TEST(NpcTest, SetXY) {
    Bear bear(10, 20, "Mishka");
    bear.setX(50);
    bear.setY(60);
    EXPECT_EQ(bear.getX(), 50);
    EXPECT_EQ(bear.getY(), 60);
}

// Тест 8: Проверка убийства NPC
TEST(NpcTest, KillNpc) {
    Bear bear(0, 0, "Mishka");
    EXPECT_TRUE(bear.isAlive());
    bear.kill();
    EXPECT_FALSE(bear.isAlive());
}

// Тест 9: Проверка потокобезопасности getX/getY
TEST(NpcTest, ThreadSafetyGetPosition) {
    Bear bear(0, 0, "Mishka");
    std::vector<std::thread> threads;
    
    // Запускаем 10 потоков, которые читают позицию
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&bear]() {
            for (int j = 0; j < 100; ++j) {
                int x = bear.getX();
                int y = bear.getY();
                EXPECT_GE(x, 0);
                EXPECT_GE(y, 0);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

// Тест 10: Проверка потокобезопасности setPosition
TEST(NpcTest, ThreadSafetySetPosition) {
    Bear bear(0, 0, "Mishka");
    std::vector<std::thread> threads;
    
    // Запускаем 5 потоков, которые изменяют позицию
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&bear, i]() {
            for (int j = 0; j < 50; ++j) {
                bear.setPosition(i * 10 + j, i * 20 + j);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Проверяем, что NPC все еще в валидном состоянии
    EXPECT_NO_THROW({
        int x = bear.getX();
        int y = bear.getY();
        EXPECT_GE(x, 0);
        EXPECT_GE(y, 0);
    });
}

// Тест 11: Проверка потокобезопасности kill/isAlive
TEST(NpcTest, ThreadSafetyKill) {
    Bear bear(0, 0, "Mishka");
    std::vector<std::thread> threads;
    
    // Запускаем несколько потоков, которые пытаются убить NPC
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&bear]() {
            for (int j = 0; j < 10; ++j) {
                bear.kill();
                EXPECT_FALSE(bear.isAlive());
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    EXPECT_FALSE(bear.isAlive());
}

// Тест 12: Проверка всех типов NPC
TEST(NpcTest, AllNpcTypes) {
    Bear bear(10, 20, "Bear");
    Bittern bittern(30, 40, "Bittern");
    Desman desman(50, 60, "Desman");
    
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bittern.getType(), "Bittern");
    EXPECT_EQ(desman.getType(), "Desman");
}
