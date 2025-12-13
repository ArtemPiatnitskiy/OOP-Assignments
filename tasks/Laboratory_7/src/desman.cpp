#include "../include/desman.h"
#include "../include/visitor.h"
#include <iostream>

Desman::Desman(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string Desman::kType = "Desman";

void Desman::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Desman::printInfo() const {
    // Специфическая информация для десмана
    std::cout << "Desman Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}