#include "../include/bear.h"
#include "../include/visitor.h"
#include <iostream>
#include <cmath>
#include <ostream>

Bear::Bear(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string Bear::kType = "Bear";

void Bear::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Bear::printInfo() const {
    // Специфическая информация для медведя
    std::cout << "Bear Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}