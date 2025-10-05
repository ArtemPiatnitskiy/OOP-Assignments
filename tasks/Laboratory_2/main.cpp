#include <iostream>
#include "include/Octal.h"

int main() {
    Octal a("7");
    Octal b("1");
    Octal s = a.add(b);
    std::cout << a.to_string() << " + " << b.to_string() << " = " << s.to_string() << '\n';

    Octal x("155");
    Octal y("137");
    Octal d = x.subtract(y);
    std::cout << x.to_string() << " - " << y.to_string() << " = " << d.to_string() << '\n';

    Octal big1("777");
    Octal big2("1");
    std::cout << big1.to_string() << " + " << big2.to_string() << " = "
              << big1.add(big2).to_string() << '\n';

    std::cout << "compare(7,1) = " << a.compare(b) << '\n';
    std::cout << "equals(7,7) = " << Octal("7").equals(a) << '\n';

    return 0;
}