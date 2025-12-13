#include "../include/npc.h"
#include <cmath>
#include <ostream>
#include <iostream>
#include <mutex>

Npc::Npc(int x, int y, const std::string& type, const std::string& name)
    : x_(x), y_(y), type_(type), name_(name), alive_(true) {}

int Npc::getX() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return x_;
}

int Npc::getY() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return y_;
}

std::string Npc::getType() const {
    return type_;
}

std::string Npc::getName() const {
    return name_;
}

void Npc::setX(int x) {
    std::lock_guard<std::mutex> lock(mutex_);
    x_ = x;
}

void Npc::setY(int y) {
    std::lock_guard<std::mutex> lock(mutex_);
    y_ = y;
}

void Npc::setPosition(int x, int y) {
    std::lock_guard<std::mutex> lock(mutex_);
    x_ = x;
    y_ = y;
}

double Npc::distanceTo(const Npc& other) const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::lock_guard<std::mutex> lock_other(other.mutex_);
    int dx = x_ - other.x_;
    int dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

bool Npc::isAlive() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return alive_;
}

void Npc::kill() {
    std::lock_guard<std::mutex> lock(mutex_);
    alive_ = false;
}

void Npc::printInfo() const {
    std::cout << this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Npc& npc) {
    std::lock_guard<std::mutex> lock(npc.mutex_);
    os << "NPC Type: " << npc.type_ << ", Name: " << npc.name_
       << ", Position: (" << npc.x_ << ", " << npc.y_ << ")";
    if (!npc.alive_) {
        os << " [DEAD]";
    }
    return os;
}