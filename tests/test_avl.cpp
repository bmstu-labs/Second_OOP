#include <iostream>
#include "tree.hpp"

    
void run_test(bool condition, const std::string& test_name) {
    static unsigned int counter = 1;
    if (condition) {
        std::cout << counter << ": " << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << counter << ": " << "[FAIL] " << test_name << std::endl;
    }
    counter++;
}

int main() {
    // Тест 1: Пустое дерево
    {
        Tree<int> tree;
        run_test(tree.is_empty(), "Empty tree");
        run_test(tree.size() == 0, "Size of empty tree");
    }

    // Тест 2: Вставка одного элемента
    {
        Tree<int> tree;
        tree.insert(10);
        run_test(!tree.is_empty(), "Tree with one element");
        run_test(tree.size() == 1, "Size of tree with one element");
        run_test(tree.find(10), "Find element in tree");
    }

    // Тест 3: Вставка нескольких элементов
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(5);
        run_test(tree.size() == 3, "Size of tree with three elements");
        run_test(tree.find(10), "Find 10 in tree");
        run_test(tree.find(20), "Find 20 in tree");
        run_test(tree.find(5), "Find 5 in tree");
    }

    // Тест 4: Удаление элемента
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(5);
        tree.remove(10);
        run_test(!tree.find(10), "Remove element from tree");
        run_test(tree.size() == 2, "Size of tree after removal");
    }

    // Тест 5: Удаление корня дерева
    {
        Tree<int> tree;
        tree.insert(10);
        tree.remove(10);
        run_test(tree.is_empty(), "Remove root from tree");
        run_test(tree.size() == 0, "Size of tree after removing root");
    }

    // Тест 6: Удаление элемента, которого нет в дереве
    {
        Tree<int> tree;
        tree.insert(10);
        tree.remove(20);  // Элемент 20 не существует
        run_test(tree.size() == 1, "Size of tree after removing non-existent element");
        run_test(tree.find(10), "Element 10 still exists in tree");
    }

    // Тест 7: Балансировка дерева после вставки
   {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(20);
        tree.insert(25);
        tree.insert(30);  // Вставка приведет к балансировке
        run_test(tree.size() == 5, "Size of tree after balancing");
        run_test(tree.find(10), "Find 10 after balancing");
        run_test(tree.find(20), "Find 20 after balancing");
        run_test(tree.find(25), "Find 25 after balancing");
    }

    // Тест 8: Проверка преобразования дерева в массив
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        std::vector<int> array = tree.to_array();
        run_test(array == std::vector<int>({5, 10, 15}), "Tree to array conversion");
    }

    // Тест 9: Проверка на большое количество элементов
    {
        Tree<int> tree;
        for (int i = 0; i < 1000; ++i) {
            tree.insert(i);
        }
        run_test(tree.size() == 1000, "Size of tree with 1000 elements");
        run_test(tree.find(500), "Find element 500 in tree");
    }

    // Тест 10: Проверка на повторяющиеся элементы
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(10);  // Не добавится
        run_test(tree.size() == 1, "Size of tree with duplicate element");
        run_test(tree.find(10), "Find duplicate element in tree");
    }

    // Тест 11: Вставка элементов в уже сбалансированное дерево
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(2);
        tree.insert(7);
        run_test(tree.size() == 5, "Size of tree with balanced insertion");
        run_test(tree.find(7), "Find 7 in balanced tree");
        run_test(tree.find(15), "Find 15 in balanced tree");
    }

    // Тест 12: Проверка на элемент, который не существует
    {
        Tree<int> tree;
        tree.insert(10);
        run_test(!tree.find(20), "Find non-existent element");
    }

    // Тест 13: Проверка на пустое дерево при удалении
    {
        Tree<int> tree;
        tree.remove(10);  // Нет элемента для удаления
        run_test(tree.is_empty(), "Tree is empty after removal attempt");
    }

    // Тест 14: Печать дерева после операций
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(20);
        tree.remove(10);
        run_test(tree.find(5), "Find 5 after removing root");
        run_test(tree.find(20), "Find 20 after removing root");
    }

    // Тест 15: Проверка на неправильный порядок вставки
    {
        Tree<int> tree;
        tree.insert(10);
        tree.insert(15);
        tree.insert(5);
        tree.insert(20);
        tree.insert(3);
        tree.insert(7);
        tree.insert(18);
        tree.insert(25);
        run_test(tree.size() == 8, "Size of tree after mixed insertion");
        run_test(tree.find(18), "Find 18 after mixed insertion");
        run_test(tree.find(25), "Find 25 after mixed insertion");
    }

    return 0;
}
