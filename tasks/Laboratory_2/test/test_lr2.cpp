#include "../include/Octal.h"
#include <gtest/gtest.h>

// Конструкторы
TEST(OctalCtor, DefaultIsZero) {
    Octal a;
    EXPECT_EQ(a.to_string(), "0");
}

TEST(OctalCtor, SizeFill) {
    Octal a(3, 7); // digits [7,7,7] -> "777"
    EXPECT_EQ(a.to_string(), "777");
}

TEST(OctalCtor, InitializerListOrderAndNormalize) {
    Octal a{1,2,3}; // Числа в списке - цифры в восьмеричной системе, младший разряд - первый элемент списка, т.е. создаётся число 321
    EXPECT_EQ(a.to_string(), "321");

    Octal z{0,0,0};
    EXPECT_EQ(z.to_string(), "0"); // Нормализованное представление
}

TEST(OctalCtor, FromInvalidSizeErrors) {
    EXPECT_THROW(Octal{9}, std::invalid_argument); // 9 не является цифрой в восьмеричной системе
}

TEST(OctalCtor, FromStringValidAndInvalid) {
    Octal a("1275"); // Создаётся число 1275 в восьмеричной системе как строку
    EXPECT_EQ(a.to_string(), "1275");

    EXPECT_THROW(Octal("89"), std::invalid_argument); // 8 и 9 не являются цифрами в восьмеричной системе
}

TEST(OctalCtor, InitializerListInvalid) {
    EXPECT_THROW(Octal{8}, std::invalid_argument); // 8 не является цифрой в восьмеричной системе
}

// Copy and Move
TEST(OctalCopyMove, CopyAndMoveBehavior) {
    Octal a("45");
    Octal b(a); // Копирование
    EXPECT_EQ(b.to_string(), "45");

    Octal c(std::move(a)); // перемещение
    // Переведённый объект a находится в неопределённом состоянии, но должен корректно разрушаться
    EXPECT_EQ(c.to_string(), "45");
    EXPECT_EQ(a.to_string(), "0");
}

// Сложение
TEST(OctalAdd, SimpleAndCarry) {
    Octal a("7");
    Octal b("1");
    EXPECT_EQ(a.add(b).to_string(), "10");

    Octal x("7");
    Octal y("7");
    EXPECT_EQ(x.add(y).to_string(), "16"); // 7+7 = 16 в восьмеричной системе
}

TEST(OctalAdd, MultiDigitCarry) {
    Octal a("777");
    Octal b("1");
    EXPECT_EQ(a.add(b).to_string(), "1000");

    Octal c("1234");
    Octal d("5");
    EXPECT_EQ(c.add(d).to_string(), "1241"); // 4 + 5 = 11 -> 1 с переносом 1, 3 + 1 = 4, остальные цифры без изменений
}

TEST(OctalAdd, ZeroPlusZero) {
    Octal z1("0"), z2("0");
    EXPECT_EQ(z1.add(z2).to_string(), "0");
}

// Вычитание
TEST(OctalSub, BasicAndBorrowChain) {
    Octal a("155");
    Octal b("137");
    EXPECT_EQ(a.subtract(b).to_string(), "16"); // 016 -> "16"

    Octal big("1000");
    Octal one("1");
    EXPECT_EQ(big.subtract(one).to_string(), "777");
}

TEST(OctalSub, ZeroAndUnderflow) {
    Octal z("0");
    EXPECT_EQ(z.subtract(z).to_string(), "0");

    Octal small("1"), larger("2");
    EXPECT_THROW(small.subtract(larger), std::underflow_error);
}

// Сравнение
TEST(OctalCompare, CompareEqualsLess) {
    Octal a("10");
    Octal b("7");
    EXPECT_GT(a.compare(b), 0);
    EXPECT_FALSE(a.equals(b));
    EXPECT_TRUE(b.less_than(a));

    Octal same1("007"); // Нормализованное представление
    Octal same2("7");
    EXPECT_EQ(same1.compare(same2), 0);
    EXPECT_TRUE(same1.equals(same2));
}

// Нормализация
TEST(OctalNormalize, ExplicitCall) {
    Octal raw{0,0,1,0}; // digits [0,0,1,0] -> В восьмеричной системе это 0100 и нормализуется до 100
    Octal norm = raw.to_string();
    EXPECT_EQ(norm.to_string(), "100");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}