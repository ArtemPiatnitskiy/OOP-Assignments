#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/bear.h"
#include "../include/bittern.h"
#include "../include/desman.h"
#include <memory>

// Тесты создания NPC
TEST(NpcTest, CreateBear) {
    Bear bear(100, 200, "Mishka");
    
    EXPECT_EQ(bear.getX(), 100);
    EXPECT_EQ(bear.getY(), 200);
    EXPECT_EQ(bear.getName(), "Mishka");
    EXPECT_EQ(bear.getType(), "Bear");
}

TEST(NpcTest, CreateBittern) {
    Bittern bittern(150, 250, "Vypochka");
    
    EXPECT_EQ(bittern.getX(), 150);
    EXPECT_EQ(bittern.getY(), 250);
    EXPECT_EQ(bittern.getName(), "Vypochka");
    EXPECT_EQ(bittern.getType(), "Bittern");
}

TEST(NpcTest, CreateDesman) {
    Desman desman(50, 75, "Vyhuhol");
    
    EXPECT_EQ(desman.getX(), 50);
    EXPECT_EQ(desman.getY(), 75);
    EXPECT_EQ(desman.getName(), "Vyhuhol");
    EXPECT_EQ(desman.getType(), "Desman");
}

// Тест расстояния между NPC
TEST(NpcTest, DistanceCalculation) {
    Bear bear1(0, 0, "Bear1");
    Bear bear2(3, 4, "Bear2");
    
    // Расстояние должно быть 5 (теорема Пифагора: 3^2 + 4^2 = 25, sqrt(25) = 5)
    EXPECT_DOUBLE_EQ(bear1.distanceTo(bear2), 5.0);
}

TEST(NpcTest, DistanceSamePosition) {
    Desman desman1(100, 100, "Desman1");
    Desman desman2(100, 100, "Desman2");
    
    EXPECT_DOUBLE_EQ(desman1.distanceTo(desman2), 0.0);
}

TEST(NpcTest, DistanceSymmetric) {
    Bittern bittern(10, 20, "Bittern1");
    Bear bear(50, 80, "Bear1");
    
    // Расстояние должно быть одинаковым в обе стороны
    EXPECT_DOUBLE_EQ(bittern.distanceTo(bear), bear.distanceTo(bittern));
}

// Тест координат на границах
TEST(NpcTest, BoundaryCoordinates) {
    Bear bear1(0, 0, "MinCorner");
    EXPECT_EQ(bear1.getX(), 0);
    EXPECT_EQ(bear1.getY(), 0);
    
    Bear bear2(500, 500, "MaxCorner");
    EXPECT_EQ(bear2.getX(), 500);
    EXPECT_EQ(bear2.getY(), 500);
}
