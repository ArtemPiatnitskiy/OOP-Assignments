#include "../include/bittern.h"
#include "../include/visitor.h"
#include <iostream>

Bittern::Bittern(int x, int y, const std::string& name)
    : Npc(x, y, kType, name) {}

const std::string Bittern::kType = "Bittern";


void Bittern::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Bittern::printInfo() const {
    // Специфическая информация для цапли
    std::cout << "Bittern Info - Name: " << getName()
              << ", Position: (" << getX() << ", " << getY() << ")"
              << std::endl;
}