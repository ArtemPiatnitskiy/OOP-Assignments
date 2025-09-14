#include "../include/replace.h"

std::string replacechar(std::string str, int n,char old_value, char new_value) {
    if (n <= 0 || old_value == new_value) {
        return str;
    }
    int count = 0;

    for (int i{0}; i < str.length(); ++i) {
        if (str[i] == old_value) {
            count++;
        }
        if (str[i] == old_value && count == n) {
            str[i] = new_value;
            count = 0;
        }
    }
    return str;
}