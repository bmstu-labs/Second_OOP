#pragma once

#include "node.hpp"

#include <vector>

template<typename TYPE>
class Tree {
    Node<TYPE> *head;
private:
    std::size_t count_nodes(Node<TYPE> *) const noexcept;

    void destroyTree(Node<TYPE> *) noexcept;

    void to_array_helper(Node<TYPE> *, std::vector<TYPE> &) const noexcept;

    Node<TYPE> *insert_node(Node<TYPE> *, TYPE) noexcept;

    Node<TYPE> *copy_helper(Node<TYPE> *) noexcept;

    Node<TYPE> *remove_node(Node<TYPE> *, TYPE) noexcept;
public:
    Tree() noexcept;

    Tree(const Tree &) noexcept;

    Tree(const std::vector<TYPE> &) noexcept;

    ~Tree() noexcept;
public:
    void insert(TYPE) noexcept;

    void insert(const std::vector<TYPE> &) noexcept;

    void remove(TYPE) noexcept;

    bool find(TYPE) noexcept;

    std::size_t size() const noexcept;

    std::vector<TYPE> to_array() const noexcept;
};


template<typename TYPE>
Tree<TYPE>::Tree() noexcept {
    this->head = nullptr;
}


template<typename TYPE>
Tree<TYPE>::Tree(const Tree &source) noexcept {
    this->head = copy_helper(source.head);
}


template<typename TYPE>
Tree<TYPE>::Tree(const std::vector<TYPE> &array) noexcept {
    this->head = nullptr;
    this->insert(array);
}


template<typename TYPE>
Tree<TYPE>::~Tree() noexcept{
    destroyTree(this->head);
}


/*
*   Helper method for copy constructor. Copy values recursively
*/
template<typename TYPE>
Node<TYPE> *Tree<TYPE>::copy_helper(Node<TYPE> *node) noexcept {
    Node<TYPE> *copy_node = nullptr;
    if (node != nullptr) {
        copy_node = new Node<TYPE>;
        copy_node->data = node->data;
        copy_node->left = copy_helper(node->left);
        copy_node->right = copy_helper(node->right);
    }

    return copy_node;
}


/*
*   Helper method for destructor. Delete node and its children
*/
template<typename TYPE>
void Tree<TYPE>::destroyTree(Node<TYPE> *node) noexcept {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}


/*
*   Helper method for insert
*/
template<typename TYPE>
Node<TYPE> *Tree<TYPE>::insert_node(Node<TYPE> *node, TYPE value) noexcept {
    Node<TYPE>* result = node;

    if (node == nullptr) {
        result = new Node<TYPE>(value);
    } 
    else if (value < node->data) {
        node->left = insert_node(node->left, value);
        result = Node<TYPE>::balance(node);
    } 
    else if (value > node->data) {
        node->right = insert_node(node->right, value);
        result = Node<TYPE>::balance(node);
    }

    return result;
}


/*
*   Helper method for to_array. Will add an element into the vector
*/
template<typename TYPE>
void Tree<TYPE>::to_array_helper(Node<TYPE> *node, std::vector<TYPE> &array) const noexcept {
    if (node != nullptr) {
        to_array_helper(node->left, array);
        array.push_back(node->data);
        to_array_helper(node->right, array);
    }
}


/*
*   Helper method for to_array. Will add an element into the vector
*/
template<typename TYPE>
Node<TYPE>* Tree<TYPE>::remove_node(Node<TYPE>* node, TYPE value) noexcept {
    Node<TYPE>* result = node;

    if (node != nullptr) {
        if (value < node->data) {
            node->left = remove_node(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove_node(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                result = nullptr;
            }
            else if (node->left == nullptr) {
                result = node->right;
                delete node;
            }
            else if (node->right == nullptr) {
                result = node->left;
                delete node;
            }
            else {
                Node<TYPE>* minNode = node->right;
                while (minNode->left != nullptr) {
                    minNode = minNode->left;
                }

                node->data = minNode->data;
                node->right = remove_node(node->right, minNode->data);
            }
        }
    }

    return result;
}


/*
*   Helper method to count nodes
*/
template<typename TYPE>
std::size_t Tree<TYPE>::count_nodes(Node<TYPE> *node) const noexcept {
    if (node == nullptr) {
        return 0;
    }

    return 1 + count_nodes(node->right) + count_nodes(node->left);
}


/*
*   Method to insert an element into the tree
*/
template<typename TYPE>
void Tree<TYPE>::insert(TYPE value) noexcept {
    this->head = insert_node(this->head, value);
}


/*
*   Method to insert an array into the tree
*/
template<typename TYPE>
void Tree<TYPE>::insert(const std::vector<TYPE> &array) noexcept {
    for (auto value : array) {
        this->insert(value);
    }
}

/*
*   Method to remove an element
*/
template<typename TYPE>
void Tree<TYPE>::remove(TYPE value) noexcept {
    head = remove_node(head, value);
}


/*
*   Method to find an element
*/
template<typename TYPE>
bool Tree<TYPE>::find(TYPE value) noexcept {
    bool result = false;

    Node<TYPE> *current = this->head;
    while (current != nullptr) {
        if (current->data == value) {
            result = true;
            break;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return result;
}


/*
*   Method to get size of the tree
*/
template<typename TYPE>
std::size_t Tree<TYPE>::size() const noexcept {
    return count_nodes(this->head);
}


/*
*   Method to interpret tree as array
*/
template<typename TYPE>
std::vector<TYPE> Tree<TYPE>::to_array() const noexcept {
    std::vector<TYPE> result;
    to_array_helper(this->head, result);
    return result;
}