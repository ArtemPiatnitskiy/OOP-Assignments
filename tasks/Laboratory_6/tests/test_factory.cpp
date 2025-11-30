#include <gtest/gtest.h>
#include "../include/factory.h"
#include "../include/bear.h"
#include "../include/bittern.h"
#include "../include/desman.h"
#include <memory>

// Тесты фабрики
TEST(FactoryTest, CreateBear) {
    auto bear = NpcFactory::createNpc("Bear", "TestBear", 100, 200);
    
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "TestBear");
    EXPECT_EQ(bear->getX(), 100);
    EXPECT_EQ(bear->getY(), 200);
}

TEST(FactoryTest, CreateBittern) {
    auto bittern = NpcFactory::createNpc("Bittern", "TestBittern", 150, 250);
    
    ASSERT_NE(bittern, nullptr);
    EXPECT_EQ(bittern->getType(), "Bittern");
    EXPECT_EQ(bittern->getName(), "TestBittern");
}

TEST(FactoryTest, CreateDesman) {
    auto desman = NpcFactory::createNpc("Desman", "TestDesman", 50, 75);
    
    ASSERT_NE(desman, nullptr);
    EXPECT_EQ(desman->getType(), "Desman");
    EXPECT_EQ(desman->getName(), "TestDesman");
}

TEST(FactoryTest, CreateInvalidType) {
    EXPECT_THROW({
        auto npc = NpcFactory::createNpc("Dragon", "TestDragon", 100, 100);
    }, std::invalid_argument);
}

// Тесты загрузки из строки
TEST(FactoryTest, CreateFromStringBear) {
    std::string line = "Bear Mishka 100 200";
    auto bear = NpcFactory::createFromString(line);
    
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "Mishka");
    EXPECT_EQ(bear->getX(), 100);
    EXPECT_EQ(bear->getY(), 200);
}

TEST(FactoryTest, CreateFromStringBittern) {
    std::string line = "Bittern Vypochka 300 400";
    auto bittern = NpcFactory::createFromString(line);
    
    ASSERT_NE(bittern, nullptr);
    EXPECT_EQ(bittern->getType(), "Bittern");
    EXPECT_EQ(bittern->getName(), "Vypochka");
    EXPECT_EQ(bittern->getX(), 300);
    EXPECT_EQ(bittern->getY(), 400);
}

TEST(FactoryTest, CreateFromStringDesman) {
    std::string line = "Desman Vyhuhol 50 75";
    auto desman = NpcFactory::createFromString(line);
    
    ASSERT_NE(desman, nullptr);
    EXPECT_EQ(desman->getType(), "Desman");
    EXPECT_EQ(desman->getName(), "Vyhuhol");
}

TEST(FactoryTest, CreateFromStringInvalidFormat) {
    std::string line = "Bear Mishka";  // Нет координат
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}

TEST(FactoryTest, CreateFromStringInvalidType) {
    std::string line = "Wolf Wolfie 100 200";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::invalid_argument);
}

TEST(FactoryTest, CreateFromStringEmptyLine) {
    std::string line = "";
    EXPECT_THROW({
        auto npc = NpcFactory::createFromString(line);
    }, std::runtime_error);
}
