#include <iostream>
#include "include/replace.h"

int main() {
    std::string str;
    int n;
    char old_value, new_value;
    std::cout << "text: ";
    std::getline(std::cin, str);
    std::cout << "n: ";
    std::cin >> n;
    std::cout << "old_value: ";
    std::cin >> old_value;
    std::cout << "new_value: ";
    std::cin >> new_value;
    std::cout << replacechar(str, n, old_value, new_value) << std::endl;
    return 0;
}