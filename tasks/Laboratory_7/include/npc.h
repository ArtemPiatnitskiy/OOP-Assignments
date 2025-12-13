#pragma once
#include <string>
#include <memory>
#include <mutex>

class Visitor;  // Предварительное объявление класса Visitor

class Npc {
    public:
        Npc(int x, int y, const std::string& type, const std::string& name);

        virtual ~Npc() = default;

        // Геттеры
        int getX() const;
        int getY() const;
        std::string getType() const;
        std::string getName() const;

        // Сеттеры для координат (потокобезопасные)
        void setX(int x);
        void setY(int y);
        void setPosition(int x, int y);

        // Расстояние до другого NPC
        double distanceTo(const Npc& other) const;

        virtual void accept(Visitor& visitor) = 0;

        // Вывод информации об NPC
        virtual void printInfo() const;

        // friend функция для вывода NPC в поток
        friend std::ostream& operator<<(std::ostream& os, const Npc& npc);

        // Статус жизни
        bool isAlive() const;
        void kill();

        // Виртуальные методы для параметров движения
        virtual int getMoveDistance() const = 0;
        virtual int getKillDistance() const = 0;

    protected:
        mutable std::mutex mutex_;  // Для потокобезопасности

    private:
        int x_;
        int y_;
        std::string type_;
        std::string name_;
        bool alive_;
};