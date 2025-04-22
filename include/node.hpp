#pragma once

#include <vector>
#include <memory>

template<typename TYPE>
class Node {
    typedef std::shared_ptr<Node<TYPE>> node_ptr;
private:
    unsigned int height;

    TYPE data;

    std::shared_ptr<Node<TYPE>> left;

    std::shared_ptr<Node<TYPE>> right;

private:
    void update_height() noexcept;  

public:
    Node() noexcept;

    Node(TYPE) noexcept;

    ~Node() = default;
public:
    TYPE value() const noexcept;

    int get_height() const noexcept;

    std::shared_ptr<Node<TYPE>> get_left() const noexcept;

    std::shared_ptr<Node<TYPE>> get_right() const noexcept;

    int balance() const noexcept;

    void set_value(TYPE) noexcept;

    void set_left(std::shared_ptr<Node<TYPE>>) noexcept;

    void set_right(std::shared_ptr<Node<TYPE>>) noexcept;

    static std::shared_ptr<Node<TYPE>> rotate_right(std::shared_ptr<Node<TYPE>>) noexcept;
    
    static std::shared_ptr<Node<TYPE>> rotate_left(std::shared_ptr<Node<TYPE>>) noexcept;

    static std::shared_ptr<Node<TYPE>> balance(std::shared_ptr<Node<TYPE>>) noexcept;
};

template<typename TYPE>
Node<TYPE>::Node() noexcept : data(TYPE{}), height(1), left(), right() {}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) noexcept : data(value), height(1), left(), right() {}

template<typename TYPE>
TYPE Node<TYPE>::value() const noexcept {
    return this->data;
}

template<typename TYPE>
int Node<TYPE>::get_height() const noexcept {
    return this->height;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Node<TYPE>::get_left() const noexcept {
    return left;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Node<TYPE>::get_right() const noexcept {
    return right;
}

template<typename TYPE>
int Node<TYPE>::balance() const noexcept { 
    int left_height = this->left ? this->left->get_height() : 0;
    int right_height = this->right ? this->right->get_height() : 0;

    return left_height - right_height;
}

template<typename TYPE>
void Node<TYPE>::set_value(TYPE value) noexcept {
    this->data = value;
}


template<typename TYPE>
void Node<TYPE>::set_left(std::shared_ptr<Node<TYPE>> node) noexcept {
    left = node;
    this->update_height();
}

template<typename TYPE>
void Node<TYPE>::set_right(std::shared_ptr<Node<TYPE>> node) noexcept {
    right = node;
    this->update_height();
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
    const int bf = node->balance();

    // Right-heavy
    if (bf < -1) {
        if (node->right->balance() > 0) {
            node->right = rotate_right((node->right));
        }
        return rotate_left((node));
    }

    // Left-heavy
    if (bf > 1) {
        if (node->left->balance() < 0) {
            node->left = rotate_left((node->left));
        }
        return rotate_right((node));
    }

    return node;
}