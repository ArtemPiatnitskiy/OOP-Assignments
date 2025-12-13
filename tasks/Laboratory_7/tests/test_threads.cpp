#include <gtest/gtest.h>
#include "../include/arena.h"
#include "../include/factory.h"
#include "../include/console_observer.h"
#include <thread>
#include <chrono>

// Тест 1: Генерация случайных NPC
TEST(ThreadsTest, GenerateRandomNpcs) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(50);
    EXPECT_EQ(arena.getNpcCount(), 50);
}

// Тест 2: Все NPC живы после создания
TEST(ThreadsTest, AllNpcsAliveAfterGeneration) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(30);
    EXPECT_EQ(arena.getAliveCount(), 30);
}

// Тест 3: Проверка границ карты
TEST(ThreadsTest, MapBoundaries) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(50);
    
    auto alive_npcs = arena.getAliveNpcs();
    for (Npc* npc : alive_npcs) {
        EXPECT_GE(npc->getX(), 0);
        EXPECT_LE(npc->getX(), 100);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LE(npc->getY(), 100);
    }
}

// Тест 4: Запуск игры на короткое время
TEST(ThreadsTest, ShortGameRun) {
    Arena arena(100, 100);
    auto observer = std::make_shared<ConsoleObserver>();
    arena.addObserver(observer);
    arena.generateRandomNpcs(20);
    
    size_t initial_count = arena.getAliveCount();
    EXPECT_EQ(initial_count, 20);
    
    // Запускаем игру на 2 секунды
    std::thread game_thread([&arena]() {
        arena.startGame(2);
    });
    
    game_thread.join();
    
    // После игры некоторые NPC могли погибнуть
    size_t final_count = arena.getAliveCount();
    EXPECT_LE(final_count, initial_count);
}

// Тест 5: Проверка остановки игры
TEST(ThreadsTest, GameStopsCorrectly) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(10);
    
    auto start = std::chrono::steady_clock::now();
    arena.startGame(1);
    auto end = std::chrono::steady_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    
    // Игра должна остановиться примерно через 1 секунду (допускаем погрешность)
    EXPECT_GE(duration, 1);
    EXPECT_LE(duration, 3);
}

// Тест 6: Мертвые NPC не появляются в getAliveNpcs
TEST(ThreadsTest, DeadNpcsNotInAliveList) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(5);
    
    auto npcs = arena.getAliveNpcs();
    EXPECT_EQ(npcs.size(), 5);
    
    // Убиваем одного NPC
    if (!npcs.empty()) {
        npcs[0]->kill();
    }
    
    // Проверяем, что живых стало меньше
    auto alive_npcs = arena.getAliveNpcs();
    EXPECT_EQ(alive_npcs.size(), 4);
}

// Тест 7: Проверка потокобезопасности getNpcCount
TEST(ThreadsTest, ThreadSafeGetNpcCount) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(30);
    
    std::vector<std::thread> threads;
    std::atomic<bool> running{true};
    
    // Запускаем несколько потоков, которые читают количество NPC
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&arena, &running]() {
            while (running) {
                size_t count = arena.getNpcCount();
                EXPECT_EQ(count, 30);
            }
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    running = false;
    
    for (auto& t : threads) {
        t.join();
    }
}

// Тест 8: Проверка потокобезопасности getAliveCount
TEST(ThreadsTest, ThreadSafeGetAliveCount) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(20);
    
    std::vector<std::thread> threads;
    std::atomic<bool> running{true};
    
    // Запускаем потоки, которые читают количество живых
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&arena, &running]() {
            while (running) {
                size_t count = arena.getAliveCount();
                EXPECT_LE(count, 20);
            }
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    running = false;
    
    for (auto& t : threads) {
        t.join();
    }
}

// Тест 9: Игра может запускаться несколько раз
TEST(ThreadsTest, MultipleGameRuns) {
    Arena arena(100, 100);
    arena.generateRandomNpcs(15);
    
    // Первый запуск
    arena.startGame(1);
    size_t count_after_first = arena.getAliveCount();
    
    // Второй запуск
    arena.startGame(1);
    size_t count_after_second = arena.getAliveCount();
    
    // Количество живых может только уменьшаться
    EXPECT_LE(count_after_second, count_after_first);
}

// Тест 10: Проверка работы с пустой ареной
TEST(ThreadsTest, EmptyArenaGame) {
    Arena arena(100, 100);
    EXPECT_EQ(arena.getNpcCount(), 0);
    EXPECT_EQ(arena.getAliveCount(), 0);
    
    // Игра должна корректно завершиться даже без NPC
    EXPECT_NO_THROW({
        arena.startGame(1);
    });
}
