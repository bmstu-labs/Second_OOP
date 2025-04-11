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
    Node() noexcept;

    Node(TYPE) noexcept;

    ~Node() = default;
public:
    static int get_height(Node<TYPE> *) noexcept;

    static int get_balance(Node<TYPE> *) noexcept;

    static void update_height(Node<TYPE> *) noexcept;

    static Node<TYPE> *rotate_right(Node<TYPE> *) noexcept;
    
    static Node<TYPE> *rotate_left(Node<TYPE> *) noexcept;

    static Node<TYPE> *balance(Node<TYPE> *) noexcept;
};

template<typename TYPE>
Node<TYPE>::Node() noexcept : data(TYPE{}), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) noexcept : data(value), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
int Node<TYPE>::get_height(Node<TYPE> *node) noexcept {
    return node ? node->height : 0;
}

template<typename TYPE>
int Node<TYPE>::get_balance(Node<TYPE> *node) noexcept {
    return node ? Node<TYPE>::get_height(node->left) - Node<TYPE>::get_height(node->right) : 0;
}   

template<typename TYPE>
void Node<TYPE>::update_height(Node<TYPE> *node) noexcept {
    if (node) {
        node->height = 1 + std::max(Node<TYPE>::get_height(node->left), Node<TYPE>::get_height(node->right));
    }
}

template<typename TYPE>
Node<TYPE> *Node<TYPE>::rotate_right(Node<TYPE> *y) noexcept {
    Node<TYPE> *x = y->left;
    Node<TYPE> *T2 = x->right;

    x->right = y;
    y->left = T2;

    Node<TYPE>::update_height(y);
    Node<TYPE>::update_height(x);

    return x;
}

template<typename TYPE>
Node<TYPE> *Node<TYPE>::rotate_left(Node<TYPE> *x) noexcept {
    Node<TYPE> *y = x->right;
    Node<TYPE> *T2 = y->left;

    y->left = x;
    x->right = T2;

    Node<TYPE>::update_height(y);
    Node<TYPE>::update_height(x);

    return y;
}

template<typename TYPE>
Node<TYPE>* Node<TYPE>::balance(Node<TYPE>* node) noexcept {
    Node<TYPE>::update_height(node);
    int balance_factor = Node<TYPE>::get_balance(node);

    Node<TYPE>* rotated_node = node;

    if (balance_factor > 1) {
        if (Node<TYPE>::get_balance(node->left) < 0) {
            node->left = Node<TYPE>::rotate_left(node->left);
        }
        rotated_node = Node<TYPE>::rotate_right(node);
    }

    if (balance_factor < -1) {
        if (Node<TYPE>::get_balance(node->right) > 0) {
            node->right = Node<TYPE>::rotate_right(node->right);
        }
        rotated_node = Node<TYPE>::rotate_left(node);
    }

    return rotated_node;
}

