cmake_minimum_required(VERSION 3.12)
project(AVLTree CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Главная библиотека (header-only)
add_library(avl_tree INTERFACE)
target_include_directories(avl_tree INTERFACE include)

add_executable(
    avl_tests
    tests/test_avl.cpp
)

target_link_libraries(avl_tests avl_tree)

add_custom_target(
    run_tests
    COMMAND avl_tests
    DEPENDS avl_tests
    COMMENT "Running tests..."
)