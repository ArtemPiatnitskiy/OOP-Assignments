#include "../include/combat_visitor.h"

bool CombatVisitor::canKill(Npc* attacker, Npc* defender) {
    if (attacker->getType() == "Bear") {
        return bearVs(defender->getType());
    } else if (attacker->getType() == "Desman") {
        return desmanVs(defender->getType());
    } else if (attacker->getType() == "Bittern") {
        return bitternVs(defender->getType());
    }
    return false;
}

bool CombatVisitor::bearVs(const std::string& defenderType) {
    // Мудеведь ест всех, кроме медведей
    return (defenderType != "Bear");
}

bool CombatVisitor::desmanVs(const std::string& defenderType) {
    // Выхухоль есть медведей
    return (defenderType == "Bear");
}

bool CombatVisitor::bitternVs(const std::string&) {
    // Выпь никого не обижает
    return false;
}