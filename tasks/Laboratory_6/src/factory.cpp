#include <memory>
#include <iostream>
#include "../include/factory.h"
#include "../include/bear.h"
#include "../include/bittern.h"
#include "../include/desman.h"
#include <sstream>
#include <stdexcept>

std::unique_ptr<Npc> NpcFactory::createNpc(
    const std::string& type,
    const std::string& name,
    int x,
    int y)
    {
        if (type == "Bear") {
            return std::make_unique<Bear>(x, y, name);
        } else if (type == "Desman") {
            return std::make_unique<Desman>(x, y, name);
        } else if (type == "Bittern") {
            return std::make_unique<Bittern>(x, y, name);
        } else {
            throw std::invalid_argument("Unknown NPC type: " + type);
        }   
    }

std::unique_ptr<Npc> NpcFactory::createFromString(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    int x, y;

    iss >> type >> name >> x >> y;
    
    if (iss.fail()) {
        throw std::runtime_error("Failed to read line: " + line);
    }

    return createNpc(type, name, x ,y);
}