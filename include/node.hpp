#pragma once

#include <vector>
#include <memory>

template<typename TYPE>
class Node {
    unsigned int height;
public:
    TYPE data;
    std::unique_ptr<Node<TYPE>> left;
    std::unique_ptr<Node<TYPE>> right;
public:
    Node() noexcept;

    Node(TYPE) noexcept;

    ~Node() = default;
public:
    static int get_height(const std::unique_ptr<Node<TYPE>> &) noexcept;

    static int get_balance(const std::unique_ptr<Node<TYPE>> &) noexcept;

    static void update_height(std::unique_ptr<Node<TYPE>> &) noexcept;

    static std::unique_ptr<Node<TYPE>> rotate_right(std::unique_ptr<Node<TYPE>>) noexcept;
    
    static std::unique_ptr<Node<TYPE>> rotate_left(std::unique_ptr<Node<TYPE>>) noexcept;

    static std::unique_ptr<Node<TYPE>> balance(std::unique_ptr<Node<TYPE>>) noexcept;
};

template<typename TYPE>
Node<TYPE>::Node() noexcept : data(TYPE{}), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) noexcept : data(value), height(1), left(nullptr), right(nullptr) {}

template<typename TYPE>
int Node<TYPE>::get_height(const std::unique_ptr<Node<TYPE>> &node) noexcept {
    return node ? node->height : 0;
}

template<typename TYPE>
int Node<TYPE>::get_balance(const std::unique_ptr<Node<TYPE>> &node) noexcept {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

template<typename TYPE>
void Node<TYPE>::update_height(std::unique_ptr<Node<TYPE>> &node) noexcept {
    if (node) {
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    }
}

template<typename TYPE>
std::unique_ptr<Node<TYPE>> Node<TYPE>::rotate_right(std::unique_ptr<Node<TYPE>> y) noexcept {
    if (!y || !y->left) return y;
    
    auto x = std::move(y->left);
    y->left = std::move(x->right);
    x->right = std::move(y);
    
    update_height(x->right);
    update_height(x);
    return x;
}

template<typename TYPE>
std::unique_ptr<Node<TYPE>> Node<TYPE>::rotate_left(std::unique_ptr<Node<TYPE>> x) noexcept {
    if (!x || !x->right) return x;
    
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    y->left = std::move(x);
    
    update_height(y->left);
    update_height(y);
    return y;
}

template<typename TYPE>
std::unique_ptr<Node<TYPE>> Node<TYPE>::balance(std::unique_ptr<Node<TYPE>> node) noexcept {
    if (!node) return nullptr;

    update_height(node);
    const int bf = get_balance(node);

    // Right-heavy
    if (bf < -1) {
        if (get_balance(node->right) > 0) {
            node->right = rotate_right(std::move(node->right));
        }
        return rotate_left(std::move(node));
    }

    // Left-heavy
    if (bf > 1) {
        if (get_balance(node->left) < 0) {
            node->left = rotate_left(std::move(node->left));
        }
        return rotate_right(std::move(node));
    }

    return node;
}