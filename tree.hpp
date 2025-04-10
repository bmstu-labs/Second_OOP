#pragma once

#include "node.hpp"

#include <vector>

template<typename TYPE>
class Tree {
    Node<TYPE> *head;
private:
    void destroyTree(Node<TYPE> *);

    void to_array_helper(Node<TYPE> *, std::vector<TYPE> &) const;
public:
    Tree();

    void insert(TYPE);

    std::vector<TYPE> to_array() const;

    ~Tree();
};

template<typename TYPE>
Tree<TYPE>::Tree() {
    head = nullptr;
}

template<typename TYPE>
Tree<TYPE>::~Tree() {
    destroyTree(head);
}

/*
*   Helper method for destructor. Delete node and its children
*/
template<typename TYPE>
void Tree<TYPE>::destroyTree(Node<TYPE> *node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

/*
*   Helper method for to_array. Will add an element into the vector
*/
template<typename TYPE>
void Tree<TYPE>::to_array_helper(Node<TYPE> *node, std::vector<TYPE> &array) const {
    if (node != nullptr) {
        to_array_helper(node->left, array);
        array.push_back(node->data);
        to_array_helper(node->right, array);
    }
}

/*
*   Method to insert an element into the tree
*/
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

/*
*   Method to interpret tree as array
*/
template<typename TYPE>
std::vector<TYPE> Tree<TYPE>::to_array() const {
    std::vector<TYPE> result;
    to_array_helper(head, result);
    return result;
}