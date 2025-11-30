# SOLID Принципы в объектно-ориентированном программировании

## Что такое SOLID?

**SOLID** — это акроним пяти основных принципов объектно-ориентированного программирования и проектирования, предложенных Робертом Мартином (Uncle Bob). Эти принципы помогают создавать более понятный, гибкий и поддерживаемый код.

**S** — Single Responsibility Principle (Принцип единственной ответственности)  
**O** — Open/Closed Principle (Принцип открытости/закрытости)  
**L** — Liskov Substitution Principle (Принцип подстановки Барбары Лисков)  
**I** — Interface Segregation Principle (Принцип разделения интерфейса)  
**D** — Dependency Inversion Principle (Принцип инверсии зависимостей)

---

## 1. Single Responsibility Principle (SRP)

### Определение

> Каждый класс должен иметь **только одну причину для изменения**, то есть отвечать только за одну задачу.

### Зачем это нужно?

- ✅ **Упрощает понимание**: легче понять, что делает класс
- ✅ **Упрощает тестирование**: проще писать тесты для одной задачи
- ✅ **Снижает связанность**: изменение в одной части не затрагивает другую
- ✅ **Упрощает поддержку**: легче находить и исправлять ошибки

### Пример из проекта

#### ❌ Плохо (нарушение SRP):

```cpp
class Npc {
    // Данные NPC
    int x_, y_;
    std::string name_;

    // Логика боя (лишняя ответственность!)
    bool canKill(Npc* other) { /* ... */ }

    // Логика сохранения (лишняя ответственность!)
    void saveToFile(const std::string& filename) { /* ... */ }

    // Логика вывода (лишняя ответственность!)
    void printToConsole() { /* ... */ }
};
```

**Проблема:** класс `Npc` отвечает за:

1. Хранение данных NPC
2. Логику боя
3. Сохранение в файл
4. Вывод на экран

#### ✅ Хорошо (соблюдение SRP):

```cpp
// 1. Класс NPC отвечает ТОЛЬКО за свои данные
class Npc {
    int x_, y_;
    std::string name_;

public:
    int getX() const;
    int getY() const;
    std::string getName() const;
    double distanceTo(const Npc& other) const;
};

// 2. CombatVisitor отвечает ТОЛЬКО за логику боя
class CombatVisitor {
public:
    bool canKill(Npc* attacker, Npc* defender);
};

// 3. Arena отвечает ТОЛЬКО за управление коллекцией NPC
class Arena {
    std::map<std::string, std::unique_ptr<Npc>> npcs_;
public:
    void addNpc(std::unique_ptr<Npc> npc);
    void saveToFile(const std::string& filename);
};

// 4. Observer отвечает ТОЛЬКО за логирование
class ConsoleObserver : public Observer {
public:
    void notify(const std::string& event) override;
};
```

**Преимущества:**

- Изменение логики боя → меняем только `CombatVisitor`
- Изменение формата сохранения → меняем только `Arena::saveToFile()`
- Изменение вывода → меняем только `Observer`

---

## 2. Open/Closed Principle (OCP)

### Определение

> Программные сущности должны быть **открыты для расширения**, но **закрыты для модификации**.

### Зачем это нужно?

- ✅ **Безопасность**: не ломаем существующий код
- ✅ **Гибкость**: легко добавляем новую функциональность
- ✅ **Стабильность**: меньше риск внесения багов
- ✅ **Масштабируемость**: система легко растёт

### Пример из проекта

#### ❌ Плохо (нарушение OCP):

```cpp
class NpcFactory {
public:
    std::unique_ptr<Npc> createNpc(const std::string& type, ...) {
        if (type == "Bear") {
            return std::make_unique<Bear>(...);
        } else if (type == "Bittern") {
            return std::make_unique<Bittern>(...);
        } else if (type == "Desman") {
            return std::make_unique<Desman>(...);
        }
        // Для добавления нового типа нужно ИЗМЕНИТЬ этот код! ❌
    }
};
```

**Проблема:** при добавлении нового типа NPC (например, `Wolf`) нужно **модифицировать** существующий метод.

#### ✅ Хорошо (соблюдение OCP):

В нашем проекте мы используем паттерн Factory, который позволяет расширять систему:

```cpp
// Базовый класс открыт для расширения
class Npc {
public:
    virtual ~Npc() = default;
    virtual void accept(Visitor& visitor) = 0;
};

// Добавляем новый тип — НЕ меняя существующие классы
class Wolf : public Npc {  // Расширение ✅
public:
    Wolf(int x, int y, const std::string& name);
    void accept(Visitor& visitor) override;
};

// В фабрике просто добавляем новую ветку
std::unique_ptr<Npc> NpcFactory::createNpc(...) {
    // ... существующий код не меняется ...
    else if (type == "Wolf") {  // Добавление ✅
        return std::make_unique<Wolf>(...);
    }
}
```

**Ещё лучше:** использовать регистрацию фабрик:

```cpp
// Идеальный вариант (не реализован в проекте, но как пример)
class NpcFactory {
    using Creator = std::function<std::unique_ptr<Npc>(...)>;
    static std::map<std::string, Creator> creators_;

public:
    static void registerCreator(const std::string& type, Creator creator) {
        creators_[type] = creator;  // Регистрация нового типа ✅
    }

    static std::unique_ptr<Npc> createNpc(const std::string& type, ...) {
        return creators_[type](...);  // Создание без if-ов ✅
    }
};
```

**Преимущества:**

- Новые типы NPC не требуют изменения существующего кода
- Можно добавлять типы динамически
- Легче тестировать

---

## 3. Liskov Substitution Principle (LSP)

### Определение

> Объекты базового класса должны **без проблем заменяться** объектами производных классов, не нарушая корректность программы.

### Зачем это нужно?

- ✅ **Полиморфизм**: истинная взаимозаменяемость объектов
- ✅ **Предсказуемость**: поведение подклассов соответствует ожиданиям
- ✅ **Надёжность**: нет неожиданных исключений или поведения
- ✅ **Повторное использование**: код работает с любыми наследниками

### Пример из проекта

#### ✅ Хорошо (соблюдение LSP):

```cpp
// Базовый класс определяет контракт
class Npc {
public:
    virtual ~Npc() = default;

    // Все наследники ОБЯЗАНЫ реализовать
    virtual void accept(Visitor& visitor) = 0;

    // Все наследники наследуют это поведение
    double distanceTo(const Npc& other) const {
        int dx = x_ - other.x_;
        int dy = y_ - other.y_;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// Наследники соблюдают контракт
class Bear : public Npc {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);  // Корректная реализация ✅
    }
};

class Desman : public Npc {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);  // Корректная реализация ✅
    }
};
```

**Использование:**

```cpp
void processBattle(Npc* npc1, Npc* npc2) {
    // Можем использовать ЛЮБОЙ тип NPC
    double distance = npc1->distanceTo(*npc2);

    CombatVisitor visitor;
    npc1->accept(visitor);  // Работает для Bear, Desman, Bittern
}

// Вызов
Bear bear(...);
Desman desman(...);
processBattle(&bear, &desman);  // ✅ Работает!
```

#### ❌ Плохо (нарушение LSP):

```cpp
class Npc {
public:
    virtual int getAttackPower() const { return 10; }
};

class Bittern : public Npc {
public:
    int getAttackPower() const override {
        throw std::runtime_error("Bittern doesn't attack!");  // ❌
    }
};

// Использование
void attack(Npc* npc) {
    int power = npc->getAttackPower();  // Может выбросить исключение!
}
```

**Проблема:** `Bittern` нарушает контракт базового класса — клиентский код ожидает получить число, но получает исключение.

**Правильное решение** (как в проекте):

```cpp
// В CombatVisitor
bool canKill(Npc* attacker, Npc* defender) {
    if (attacker->getType() == "Bittern") {
        return false;  // Выпь не атакует ✅
    }
    // ...
}
```

---

## 4. Interface Segregation Principle (ISP)

### Определение

> Клиенты **не должны зависеть** от интерфейсов, которые они не используют. Лучше много **маленьких специализированных** интерфейсов, чем один большой универсальный.

### Зачем это нужно?

- ✅ **Простота**: классы не перегружены лишними методами
- ✅ **Гибкость**: можно реализовать только нужное
- ✅ **Независимость**: изменения в одном интерфейсе не влияют на другой
- ✅ **Тестируемость**: проще мокировать маленькие интерфейсы

### Пример из проекта

#### ✅ Хорошо (соблюдение ISP):

```cpp
// Маленький специализированный интерфейс для наблюдателей
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const std::string& event) = 0;  // Только одно!
};

// Реализация для консоли
class ConsoleObserver : public Observer {
public:
    void notify(const std::string& event) override {
        std::cout << "[BATTLE] " << event << std::endl;
    }
};

// Реализация для файла
class FileObserver : public Observer {
public:
    void notify(const std::string& event) override {
        std::ofstream file(filename_, std::ios::app);
        file << event << std::endl;
    }
};
```

**Преимущества:**

- Наблюдатели знают **только** про `notify()`
- Можно легко добавить `DatabaseObserver`, `NetworkObserver` и т.д.
- Каждый наблюдатель реализует **только то, что ему нужно**

#### ❌ Плохо (нарушение ISP):

```cpp
// Большой "жирный" интерфейс
class ILogger {
public:
    virtual void logToConsole(const std::string& msg) = 0;
    virtual void logToFile(const std::string& msg) = 0;
    virtual void logToDatabase(const std::string& msg) = 0;
    virtual void logToNetwork(const std::string& msg) = 0;
    virtual void sendEmail(const std::string& msg) = 0;
};

// ConsoleLogger должен реализовать ВСЕ методы! ❌
class ConsoleLogger : public ILogger {
public:
    void logToConsole(const std::string& msg) override { /* ... */ }

    // Не нужны, но обязаны реализовать! ❌
    void logToFile(const std::string&) override { throw std::logic_error("Not supported"); }
    void logToDatabase(const std::string&) override { throw std::logic_error("Not supported"); }
    void logToNetwork(const std::string&) override { throw std::logic_error("Not supported"); }
    void sendEmail(const std::string&) override { throw std::logic_error("Not supported"); }
};
```

**Проблема:** класс вынужден реализовывать методы, которые ему не нужны.

---

## 5. Dependency Inversion Principle (DIP)

### Определение

> 1. Модули верхнего уровня **не должны зависеть** от модулей нижнего уровня. Оба должны зависеть от **абстракций**.
> 2. Абстракции **не должны зависеть** от деталей. Детали должны зависеть от абстракций.

### Зачем это нужно?

- ✅ **Слабая связанность**: модули независимы друг от друга
- ✅ **Гибкость**: легко заменять реализации
- ✅ **Тестируемость**: можно легко мокировать зависимости
- ✅ **Расширяемость**: добавление новых реализаций без изменения кода

### Пример из проекта

#### ❌ Плохо (нарушение DIP):

```cpp
class Arena {
    std::map<std::string, std::unique_ptr<Npc>> npcs_;

    // Зависимость от конкретных классов! ❌
    ConsoleObserver consoleObserver_;
    FileObserver fileObserver_;

public:
    void notifyBattle(const std::string& event) {
        consoleObserver_.log(event);  // Жёсткая привязка ❌
        fileObserver_.log(event);     // Жёсткая привязка ❌
    }
};
```

**Проблема:**

- `Arena` знает о **конкретных** классах наблюдателей
- Нельзя добавить новый тип наблюдателя без изменения `Arena`
- Сложно тестировать

#### ✅ Хорошо (соблюдение DIP):

```cpp
// Абстракция (интерфейс)
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const std::string& event) = 0;
};

// Arena зависит от АБСТРАКЦИИ, а не от конкретных классов ✅
class Arena {
    std::map<std::string, std::unique_ptr<Npc>> npcs_;
    std::vector<std::shared_ptr<Observer>> observers_;  // Зависимость от абстракции ✅

public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }

    void notifyObservers(const std::string& event) {
        for (auto& observer : observers_) {
            observer->notify(event);  // Работает с любым Observer ✅
        }
    }
};

// Конкретные реализации зависят от абстракции
class ConsoleObserver : public Observer {  // ✅
public:
    void notify(const std::string& event) override { /* ... */ }
};

class FileObserver : public Observer {  // ✅
public:
    void notify(const std::string& event) override { /* ... */ }
};
```

**Использование:**

```cpp
Arena arena;

// Можем добавлять любые наблюдатели динамически ✅
arena.addObserver(std::make_shared<ConsoleObserver>());
arena.addObserver(std::make_shared<FileObserver>("log.txt"));
arena.addObserver(std::make_shared<DatabaseObserver>(db_connection));  // Новый тип!

// Arena не знает о конкретных типах — работает с абстракцией
arena.startBattle(100.0);
```

**Преимущества:**

- `Arena` не зависит от конкретных наблюдателей
- Легко добавить `DatabaseObserver`, `NetworkObserver` без изменения `Arena`
- Легко тестировать с помощью mock-объектов

**Диаграмма зависимостей:**

```
БЕЗ DIP:
Arena ──→ ConsoleObserver
      ──→ FileObserver
(высокая связанность ❌)

С DIP:
Arena ──→ Observer (интерфейс)
              ↑
              ├── ConsoleObserver
              ├── FileObserver
              └── DatabaseObserver
(низкая связанность ✅)
```

---

## Взаимосвязь паттернов проектирования и SOLID

В нашем проекте используются три паттерна проектирования, которые помогают соблюдать SOLID:

### Factory Pattern (Фабрика)

**Какие принципы SOLID соблюдает:**

- **SRP**: Создание объектов вынесено в отдельный класс
- **OCP**: Можно добавлять новые типы NPC без изменения клиентского кода
- **DIP**: Клиенты зависят от интерфейса `Npc`, а не от конкретных классов

```cpp
// Клиент не знает о конкретных типах
auto npc = NpcFactory::createNpc("Bear", 10, 20, "Mishka");
// npc имеет тип std::unique_ptr<Npc> — абстракция ✅
```

### Visitor Pattern (Посетитель)

**Какие принципы SOLID соблюдает:**

- **SRP**: Логика боя вынесена из классов NPC
- **OCP**: Можно добавлять новые операции (визиторы) без изменения NPC
- **ISP**: Интерфейс `Visitor` специализирован для одной задачи

```cpp
// Логика боя отделена от данных NPC
CombatVisitor combatVisitor;
bool canKill = combatVisitor.canKill(bear, desman);
```

### Observer Pattern (Наблюдатель)

**Какие принципы SOLID соблюдает:**

- **SRP**: Логирование вынесено в отдельные классы
- **OCP**: Можно добавлять новые наблюдатели без изменения `Arena`
- **ISP**: Интерфейс `Observer` содержит только один метод `notify()`
- **DIP**: `Arena` зависит от абстракции `Observer`, а не от конкретных классов

```cpp
// Arena работает с любыми наблюдателями
arena.addObserver(std::make_shared<ConsoleObserver>());
arena.addObserver(std::make_shared<FileObserver>("log.txt"));
```

---

## Итоги

### Почему SOLID важен?

1. **Гибкость**: Легко добавлять новую функциональность
2. **Поддерживаемость**: Понятная структура, легко вносить изменения
3. **Тестируемость**: Каждый компонент можно тестировать независимо
4. **Масштабируемость**: Система легко растёт без переписывания
5. **Переиспользование**: Компоненты можно использовать в других проектах

### Как применять на практике?

1. **Проектируй с мыслью о будущем**: Какие изменения могут потребоваться?
2. **Разделяй ответственности**: Один класс = одна задача
3. **Используй абстракции**: Зависимость от интерфейсов, а не от реализаций
4. **Расширяй, не изменяй**: Добавляй новые классы, а не меняй старые
5. **Пиши тесты**: Они покажут, насколько удачна архитектура

### Проверочные вопросы для самопроверки

1. **SRP**: Можно ли описать назначение класса **одним предложением**? Если нет — возможно, он делает слишком много.

2. **OCP**: Если нужно добавить новую функцию, придётся ли **изменять** существующие классы? Если да — нарушен OCP.

3. **LSP**: Можно ли **заменить** базовый класс на производный **без изменения** клиентского кода? Если нет — нарушен LSP.

4. **ISP**: Есть ли в интерфейсе методы, которые **не нужны** некоторым реализациям? Если да — нарушен ISP.

5. **DIP**: Зависят ли классы высокого уровня от **конкретных** классов низкого уровня? Если да — нарушен DIP.
