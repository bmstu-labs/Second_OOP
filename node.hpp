#pragma once

#include <iostream>
#include <vector>

template<typename TYPE>
class Node {
    int height;
public:
    TYPE data;
    Node *left;
    Node *right;
public:
    Node();

    Node(TYPE);

    ~Node() = default;
public:
    static int get_height(Node<TYPE> *);

    static int get_balance(Node<TYPE> *);

    static void update_height(Node<TYPE> *);

    static Node<TYPE> *rotate_right(Node<TYPE> *);
    
    static Node<TYPE> *rotate_left(Node<TYPE> *);

    static Node<TYPE> *balance(Node<TYPE> *);
};

template<typename TYPE>
Node<TYPE>::Node() : data(TYPE{}), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) : data(value), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
int Node<TYPE>::get_height(Node<TYPE> *node) {
    return node ? node->height : 0;
}

template<typename TYPE>
int Node<TYPE>::get_balance(Node<TYPE> *node) {
    return node ? Node<TYPE>::get_height(node->left) - Node<TYPE>::get_height(node->right) : 0;
}   

template<typename TYPE>
void Node<TYPE>::update_height(Node<TYPE> *node) {
    if (node) {
        node->height = 1 + std::max(Node<TYPE>::get_height(node->left), Node<TYPE>::get_height(node->right));
    }
}

template<typename TYPE>
Node<TYPE> *Node<TYPE>::rotate_right(Node<TYPE> *y) {
    Node<TYPE> *x = y->left;
    Node<TYPE> *T2 = x->right;

    x->right = y;
    y->left = T2;

    Node<TYPE>::update_height(y);
    Node<TYPE>::update_height(x);

    return x;
}

template<typename TYPE>
Node<TYPE> *Node<TYPE>::rotate_left(Node<TYPE> *x) {
    Node<TYPE> *y = x->right;
    Node<TYPE> *T2 = y->left;

    y->left = x;
    x->right = T2;

    Node<TYPE>::update_height(y);
    Node<TYPE>::update_height(x);

    return y;
}

template<typename TYPE>
Node<TYPE>* Node<TYPE>::balance(Node<TYPE>* node) {
    Node<TYPE>::update_height(node);  // Используем статический вызов для update_height
    int balance_factor = Node<TYPE>::get_balance(node);  // Статический вызов get_balance

    Node<TYPE>* rotated_node = node;

    if (balance_factor > 1) {
        // Если балансировка нужна, то сначала проверим левый поддерево для "LR" случая
        if (Node<TYPE>::get_balance(node->left) < 0) {
            node->left = Node<TYPE>::rotate_left(node->left);  // Статический вызов rotate_left
        }
        rotated_node = Node<TYPE>::rotate_right(node);  // Статический вызов rotate_right
    }

    if (balance_factor < -1) {
        // Если балансировка нужна, то сначала проверим правый поддерево для "RL" случая
        if (Node<TYPE>::get_balance(node->right) > 0) {
            node->right = Node<TYPE>::rotate_right(node->right);  // Статический вызов rotate_right
        }
        rotated_node = Node<TYPE>::rotate_left(node);  // Статический вызов rotate_left
    }

    return rotated_node;
}

