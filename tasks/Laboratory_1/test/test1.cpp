#include <gtest/gtest.h>
#include "../include/replace.h"

// Тест из задания
TEST(test_01, Task_test) {
    std::string str = "Vader said: No, I am your father!";
    std::string res = "Vader soid: No, I am your fother!";
    ASSERT_EQ(replacechar(str, 2, 'a', 'o'), res);
}

// Нет символов для замены
TEST(test_02, no_old_value) {
    std::string str = "Hello, World!";
    std::string res = "Hello, World!";
    ASSERT_EQ(replacechar(str, 3, 'x', 'y'), res);
}

// n больше количества символов в строке
TEST(test_03, n_greater_then_count) {
    std::string str = "banana";
    std::string res = "banana";
    ASSERT_EQ(replacechar(str, 10, 'a', 'o'), res);
}

// Замена всех символов
TEST(test_04, replace_all) {
    std::string str = "aaaaaa";
    std::string res = "bbbbbb";
    ASSERT_EQ(replacechar(str, 1, 'a', 'b'), res);
}

// n == 0 (ничего не меняется)
TEST(test_05, n_zero) {
    std::string str = "test";
    std::string res = "test";
    ASSERT_EQ(replacechar(str, 0, 't', 'x'), res);
}

// Пустая строка
TEST(test_06, empty_string) {
    std::string str = "";
    std::string res = "";
    ASSERT_EQ(replacechar(str, 2, 'a', 'b'), res);
}

// old_value и new_value совпадают
TEST(test_07, old_equals_new) {
    std::string str = "banana";
    std::string res = "banana";
    ASSERT_EQ(replacechar(str, 2, 'a', 'a'), res);
}

// Проверка замены каждого 3 элемента
TEST(test_08, every_third) {
    std::string str = "5 5 5 5 5 5 5 5 5 5 5";
    std::string res = "5 5 7 5 5 7 5 5 7 5 5";
    ASSERT_EQ(replacechar(str, 3, '5', '7'), res);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}