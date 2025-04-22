#pragma once

#include <vector>
#include <memory>

template<typename TYPE>
class Node {
    unsigned int height;
public:
    TYPE data;
    std::shared_ptr<Node<TYPE>> left;
    std::shared_ptr<Node<TYPE>> right;
public:
    Node() noexcept;

    Node(TYPE) noexcept;

    ~Node() = default;
public:
    TYPE get_value() const noexcept;

    int get_height() const noexcept;

    int get_balance() const noexcept;

    void update_height() noexcept;

    static std::shared_ptr<Node<TYPE>> rotate_right(std::shared_ptr<Node<TYPE>>) noexcept;
    
    static std::shared_ptr<Node<TYPE>> rotate_left(std::shared_ptr<Node<TYPE>>) noexcept;

    static std::shared_ptr<Node<TYPE>> balance(std::shared_ptr<Node<TYPE>>) noexcept;
};

template<typename TYPE>
Node<TYPE>::Node() noexcept : data(TYPE{}), height(1), left(), right() {}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) noexcept : data(value), height(1), left(), right() {}

template<typename TYPE>
TYPE Node<TYPE>::get_value() const noexcept {
    return this->data;
}

template<typename TYPE>
int Node<TYPE>::get_height() const noexcept {
    return this->height;
}

template<typename TYPE>
int Node<TYPE>::get_balance() const noexcept { 
    int left_height = this->left ? this->left->get_height() : 0;
    int right_height = this->right ? this->right->get_height() : 0;

    return left_height - right_height;
}

template<typename TYPE>
void Node<TYPE>::update_height() noexcept {
    this->height = 1 + std::max(
        this->left ? this->left->get_height() : 0,
        this->right ? this->right->get_height() : 0
    );
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Node<TYPE>::rotate_right(std::shared_ptr<Node<TYPE>> y) noexcept {
    if (!y || !y->left) return y;
    
    auto x = (y->left);
    y->left = (x->right);
    x->right = (y);
    
    x->right->update_height();
    x->update_height();
    return x;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Node<TYPE>::rotate_left(std::shared_ptr<Node<TYPE>> x) noexcept {
    if (!x || !x->right) return x;
    
    auto y = (x->right);
    x->right = (y->left);
    y->left = (x);
    
    y->left->update_height();
    y->update_height();
    return y;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Node<TYPE>::balance(std::shared_ptr<Node<TYPE>> node) noexcept {
    if (!node) return nullptr;

    node->update_height();
    const int bf = node->get_balance();

    // Right-heavy
    if (bf < -1) {
        if (node->right->get_balance() > 0) {
            node->right = rotate_right((node->right));
        }
        return rotate_left((node));
    }

    // Left-heavy
    if (bf > 1) {
        if (node->left->get_balance() < 0) {
            node->left = rotate_left((node->left));
        }
        return rotate_right((node));
    }

    return node;
}