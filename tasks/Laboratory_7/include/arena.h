#pragma once
#include <string>
#include "npc.h"
#include <map>
#include <memory>
#include "observer.h"
#include <vector>
#include <shared_mutex>
#include <queue>
#include <atomic>
#include <thread>
#include <condition_variable>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

struct BattleTask {
    Npc* attacker;
    Npc* defender;
};

class Arena {
    public:
        Arena(int width = MAX_WIDTH, int height = MAX_HEIGHT);
        ~Arena();

        // Добавление NPC на арену
        void addNpc(std::unique_ptr<Npc> npc);

        void createAndAddNpc(const std::string& type, 
                         const std::string& name, 
                         int x, int y);

        // Вывод информации обо всех NPC
        void printAllNpcs() const;

        // Получение количества NPC
        size_t getNpcCount() const;
        size_t getAliveCount() const;

        // Управление наблюдателями
        void addObserver(std::shared_ptr<Observer> observer);

        void removeObserver(std::shared_ptr<Observer> observer);

        // Управление боем (старая версия)
        void startBattle(double range);

        // Сохранение в файл
        void saveToFile(const std::string& filename) const;

        // Загрузка из файла
        void loadFromFile(const std::string& filename);

        // Очистка арены
        void clear();

        // Новые методы для многопоточности
        void startGame(int durationSeconds);
        void stopGame();

        // Генерация случайных NPC
        void generateRandomNpcs(int count);

        // Вывод карты
        void printMap() const;

        // Вывод списка выживших
        void printSurvivors() const;

        // Потокобезопасный доступ к NPC
        std::vector<Npc*> getAliveNpcs() const;

    private:
        int width_;
        int height_;
        std::map<std::string, std::unique_ptr<Npc>> npcs_;

        std::vector<std::shared_ptr<Observer>> observers_;

        // Для многопоточности
        mutable std::shared_mutex npcs_mutex_;
        mutable std::mutex observers_mutex_;
        mutable std::mutex cout_mutex_;
        
        std::queue<BattleTask> battle_queue_;
        std::mutex battle_queue_mutex_;
        std::condition_variable battle_cv_;

        std::atomic<bool> running_;

        std::thread movement_thread_;
        std::thread battle_thread_;
        std::thread print_thread_;

        void notifyObservers(const std::string& event);

        // Потоковые функции
        void movementThreadFunc();
        void battleThreadFunc();
        void printThreadFunc();

        // Вспомогательные методы
        bool isValidPosition(int x, int y) const;
};