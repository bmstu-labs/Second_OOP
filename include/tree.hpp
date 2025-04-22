#pragma once

#include "node.hpp"
#include <vector>
#include <memory>

template<typename TYPE>
class Tree {
    std::shared_ptr<Node<TYPE>> head;

    std::size_t count_nodes(const std::shared_ptr<Node<TYPE>> &node) const noexcept;

    std::shared_ptr<Node<TYPE>> insert_node(std::shared_ptr<Node<TYPE>> node, TYPE value);

    std::shared_ptr<Node<TYPE>> remove_node(std::shared_ptr<Node<TYPE>> node, TYPE value) noexcept;

    void to_array_helper(const std::shared_ptr<Node<TYPE>> &node, std::vector<TYPE> &array) const;

public:
    Tree() noexcept = default;
    
    Tree(const Tree &source);
    
    Tree(const std::vector<TYPE> &array);

    void insert(TYPE value);

    void insert(const std::vector<TYPE> &array);

    void remove(TYPE value) noexcept;

    bool find(TYPE value) noexcept;

    bool is_empty() const noexcept;

    std::size_t size() const noexcept;
    
    std::vector<TYPE> to_array() const;
};

template<typename TYPE>
std::size_t Tree<TYPE>::count_nodes(const std::shared_ptr<Node<TYPE>> &node) const noexcept {
    return node ? 1 + count_nodes(node->left) + count_nodes(node->right) : 0;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Tree<TYPE>::insert_node(std::shared_ptr<Node<TYPE>> node, TYPE value) {
    if (!node) return std::make_shared<Node<TYPE>>(value);

    if (value < node->data) {
        node->left = insert_node((node->left), value);
    } else if (value > node->data) {
        node->right = insert_node((node->right), value);
    }

    return Node<TYPE>::balance((node));
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Tree<TYPE>::remove_node(std::shared_ptr<Node<TYPE>> node, TYPE value) noexcept {
    std::shared_ptr<Node<TYPE>> result = node;

    if (node) {
        if (value < node->data) {
            node->left = remove_node(node->left, value);
        } 
        else if (value > node->data) {
            node->right = remove_node(node->right, value);
        } 
        else {
            if (!node->left && !node->right) {
                result = nullptr;
            }
            else if (!node->left) {
                result = node->right;
            }
            else if (!node->right) {
                result = node->left;
            }
            else {
                auto current = node->right;
                while (current->left) {
                    current = current->left;
                }
                node->data = current->data;
                node->right = remove_node(node->right, node->data);
            }
        }
        
        if (result) {
            result = Node<TYPE>::balance(result);
        }
    }

    return result;
}

template<typename TYPE>
void Tree<TYPE>::to_array_helper(const std::shared_ptr<Node<TYPE>> &node, std::vector<TYPE> &array) const {
    if (!node) return;
    to_array_helper(node->left, array);
    array.push_back(node->data);
    to_array_helper(node->right, array);
}

template<typename TYPE>
Tree<TYPE>::Tree(const Tree &source) {
    for (const auto &elem : source.to_array()) insert(elem);
}

template<typename TYPE>
Tree<TYPE>::Tree(const std::vector<TYPE> &array) {
    for (const auto &elem : array) {
        insert(elem);
    }
}

template<typename TYPE>
void Tree<TYPE>::insert(TYPE value) {
    head = insert_node(head, value);
}

template<typename TYPE>
void Tree<TYPE>::insert(const std::vector<TYPE> &array) {
    for (const auto &elem : array) insert(elem);
}

template<typename TYPE>
void Tree<TYPE>::remove(TYPE value) noexcept {
    head = remove_node(head, value);
}

template<typename TYPE>
bool Tree<TYPE>::find(TYPE value) noexcept {
    std::shared_ptr<Node<TYPE>> current = head;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = (value < current->data) ? current->left : current->right;
    }
    return false;
}

template<typename TYPE>
bool Tree<TYPE>::is_empty() const noexcept {
    return !head;
}

template<typename TYPE>
std::size_t Tree<TYPE>::size() const noexcept {
    return count_nodes(head);
}

template<typename TYPE>
std::vector<TYPE> Tree<TYPE>::to_array() const {
    std::vector<TYPE> result;
    to_array_helper(head, result);
    return result;
}