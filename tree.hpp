#pragma once

#include "node.hpp"

template<typename TYPE>
class Tree {
    Node<TYPE> *head;
public:
    Tree();

    void insert(TYPE);

    ~Tree();
};

template<typename TYPE>
Tree<TYPE>::Tree() {
    head = nullptr;
}

template<typename TYPE>
Tree<TYPE>::~Tree() = default;

template<typename TYPE>
void Tree<TYPE>::insert(TYPE value) {
    if (this->head != nullptr) {
        Node<TYPE> *parent, *current = this->head;
        while (current) {
            parent = current;
            current = current->data < value ? current->right : current->left;
        }
        if (parent->data < value) {
            parent->right = new Node(value);
        } 
        else {
            parent->left = new Node(value);
        }
    }
    else {
        this->head = new Node<TYPE>(value);
    }
}