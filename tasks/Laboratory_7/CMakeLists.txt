cmake_minimum_required(VERSION 3.10)
project(Laboratory_7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

# Установка Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Исходные файлы
set(SOURCES
    src/npc.cpp
    src/bear.cpp
    src/bittern.cpp
    src/desman.cpp
    src/factory.cpp
    src/arena.cpp
    src/combat_visitor.cpp
)

# Библиотека
add_library(${PROJECT_NAME}_lib ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Основной исполняемый файл
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Тестовая программа
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp)
    add_executable(${PROJECT_NAME}_test_demo test_main.cpp)
    target_link_libraries(${PROJECT_NAME}_test_demo PRIVATE ${PROJECT_NAME}_lib)
    
    # Копирование тестовых файлов
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_npcs.txt 
                   ${CMAKE_CURRENT_BINARY_DIR}/test_npcs.txt COPYONLY)
endif()

# Добавление тестов
enable_testing()

# Тесты для NPC
add_executable(${PROJECT_NAME}_test_npc tests/test_npc.cpp)
target_link_libraries(${PROJECT_NAME}_test_npc PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME ${PROJECT_NAME}_test_npc COMMAND ${PROJECT_NAME}_test_npc)

# Тесты для многопоточности
add_executable(${PROJECT_NAME}_test_threads tests/test_threads.cpp)
target_link_libraries(${PROJECT_NAME}_test_threads PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME ${PROJECT_NAME}_test_threads COMMAND ${PROJECT_NAME}_test_threads)

# Тесты для боевой системы
add_executable(${PROJECT_NAME}_test_battle tests/test_battle.cpp)
target_link_libraries(${PROJECT_NAME}_test_battle PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME ${PROJECT_NAME}_test_battle COMMAND ${PROJECT_NAME}_test_battle)
