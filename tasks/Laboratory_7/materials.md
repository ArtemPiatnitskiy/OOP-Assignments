# Лабораторная работа №7: Асинхронное программирование

##  в C++Многопоточно


- `std::atomic` - атомарные операцииcat > /workspaces/OOP-Assignments/tasks/Laboratory_7/materials.md << 'HEREDOC'
# Лабораторная работа №7: Асинхронное программир�- `std::mutex` и `std::shared_mutex` - синхрони�вание

##  в C++Многопоточно



- `std::condition_variable` - координация потоков
- Producer-Consumer паттерн для обработки боев

## Основн
### 1. Поток движения NPC (`movementThreadFunc`)
- Проверяет столкновения на дистанции убийства- Перемещает NPC на расстоян
- Создает задачи для потока боев

### 2. Поток боевой системы (`battleThreadFunc`)
- Обрабатывает очередь боев
- Убивает NPC если а- Бросает 6-гран
### 3. Поток вывода карты (`printThreadFunc`)
- Каждую секунду печатает карту
- Потокобезопасный вывод с `std::lock_guard`- Показ

## Потокобезопасность

- `npcs_` защищен `std::shared_mutex` (читатели/писатели)
- `battle_queue_` защищена `std::mutex` + `std::condition_variable`
- `std::cout` защищен `cout_mutex_`
- `running_` - `std::atomic<bool>` для флага состояния

## Запу
```bash
cd build_lab7
./Laboratory_7_exe
```

