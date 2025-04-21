# AVL Tree Implementation 🌳  
**Вторая лабораторная работа по ООП**  

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

Реализация самобалансирующегося AVL-дерева на C++ с использованием современных возможностей языка.

---

## 📖 Содержание
1. [🚀 Особенности](#-особенности)
2. [⚙️ Требования](#-требования)
3. [🔨 Сборка и установка](#-сборка-и-установка)
4. [📚 Примеры использования](#-примеры-использования)
5. [📂 Структура проекта](#-структура-проекта)
6. [🧪 Тестирование](#-тестирование)
7. [📜 Лицензия](#-лицензия)

---

<a name="-особенности"></a>
## 🚀 Особенности
- **Полная реализация AVL-дерева**:
  - Вставка элементов (одиночных и массовая)
  - Удаление элементов
  - Поиск элементов
  - Автоматическая балансировка
- **Современный C++**:
  - Шаблоны для поддержки любых типов данных
  - Умные указатели (`std::unique_ptr`)
  - STL-совместимость (`std::vector`)
- **Кроссплатформенность** (Linux, Windows, macOS)

---

<a name="-требования"></a>
## ⚙️ Требования
- Компилятор с поддержкой C++17:
  - GCC 9+
  - Clang 10+
  - MSVC 19.28+
- CMake 3.12+

---

<a name="-сборка-и-установка"></a>
## 🔨 Сборка и установка

### Linux/macOS
```bash
git clone https://github.com/yourusername/avl-tree.git
cd avl-tree
mkdir build && cd build
cmake ..
make

### Windows (PowerShell)
```bash
git clone https://github.com/yourusername/avl-tree.git
cd avl-tree
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

---

<a name="-примеры-использования"></a>
## 📚 Примеры использования
```cpp
#include "tree.hpp"
#include <iostream>

int main() {
    Tree<int> tree;
    
    // Вставка элементов
    tree.insert({50, 30, 70, 20, 40, 60, 80});  // batch insert
    
    // Удаление
    tree.remove(30);
    
    // Поиск
    if (tree.find(60)) {
        std::cout << "Элемент 60 найден!\n";
    }
    
    // Сериализация в вектор
    auto arr = tree.to_array();  // [20, 40, 50, 60, 70, 80]
    
    // Размер дерева
    std::cout << "Размер: " << tree.size() << "\n";  // 6
    
    return 0;
}
```
---

<a name="-структура-проекта"></a>
## 📂 Структура проекта

```
.
├── include/
│   ├── tree.hpp    # Интерфейс дерева
│   └── node.hpp    # Реализация узла
├── tests/
│   └── test_avl.cpp # Модульные тесты
├── CMakeLists.txt  # Конфигурация сборки
└── README.md       # Документация
```
---

<a name="-тестирование"></a>
## 🧪 Тестирование

После сборки запустите:
```bash
./build/avl_tests
```
