#pragma once

#include "node.hpp"
#include "iterator.hpp"

#include <vector>
#include <memory>

template<typename TYPE>
class Tree {
    friend class Iterator<TYPE>;
private:
    std::shared_ptr<Node<TYPE>> head;

private:
    std::size_t count_nodes(const std::shared_ptr<Node<TYPE>> &node) const noexcept;

    std::shared_ptr<Node<TYPE>> insert_node(std::shared_ptr<Node<TYPE>> node, TYPE value);

    std::shared_ptr<Node<TYPE>> remove_node(std::shared_ptr<Node<TYPE>> node, TYPE value) noexcept;

    void to_array_helper(const std::shared_ptr<Node<TYPE>> &node, std::vector<TYPE> &array) const;

    std::shared_ptr<Node<TYPE>> get_root() const;

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

public:
    Iterator<TYPE> begin() const;

    Iterator<TYPE> end() const;
};

template<typename TYPE>
std::size_t Tree<TYPE>::count_nodes(const std::shared_ptr<Node<TYPE>> &node) const noexcept {
    return node ? 1 + count_nodes(node->get_left()) + count_nodes(node->get_right()) : 0;
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Tree<TYPE>::insert_node(std::shared_ptr<Node<TYPE>> node, TYPE value) {
    if (!node) return std::make_shared<Node<TYPE>>(value);

    if (value < node->value()) {
        node->get_left() = insert_node((node->get_left()), value);
    } else if (value > node->value()) {
        node->get_right() = insert_node((node->get_right()), value);
    }

    return Node<TYPE>::balance((node));
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Tree<TYPE>::remove_node(std::shared_ptr<Node<TYPE>> node, TYPE value) noexcept {
    std::shared_ptr<Node<TYPE>> result = node;

    if (node) {
        if (value < node->value()) {
            node->get_left() = remove_node(node->get_left(), value);
        } 
        else if (value > node->value()) {
            node->get_right() = remove_node(node->get_right(), value);
        } 
        else {
            if (!node->get_left() && !node->get_right()) {
                result = nullptr;
            }
            else if (!node->get_left()) {
                result = node->get_right();
            }
            else if (!node->get_right()) {
                result = node->get_left();
            }
            else {
                auto current = node->get_right();
                while (current->get_left()) {
                    current = current->get_left();
                }
                node->set_value(current->value());
                node->set_right(remove_node(node->get_right(), node->value()));
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
    to_array_helper(node->get_left(), array);
    array.push_back(node->value());
    to_array_helper(node->get_right(), array);
}

template<typename TYPE>
std::shared_ptr<Node<TYPE>> Tree<TYPE>::get_root() const {
    return head;
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
        if (current->value() == value) {
            return true;
        }
        current = (value < current->value()) ? current->get_left() : current->get_right();
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

template<typename TYPE>
Iterator<TYPE> Tree<TYPE>::begin() const {
    return Iterator<TYPE>(*this);
}

template<typename TYPE>
Iterator<TYPE> Tree<TYPE>::end() const {
    Iterator<TYPE> it(*this);
    it.mark_as_end();
    return it;
}