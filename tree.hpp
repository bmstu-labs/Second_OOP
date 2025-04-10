#pragma once

#include "node.hpp"

#include <vector>

template<typename TYPE>
class Tree {
    Node<TYPE> *head;
private:
    void destroyTree(Node<TYPE> *);

    void to_array_helper(Node<TYPE> *, std::vector<TYPE> &) const;

    std::size_t count_nodes(Node<TYPE> *) const;

    Node<TYPE> *remove_node(Node<TYPE> *, TYPE);
public:
    Tree();

    void insert(TYPE);

    void insert(std::vector<TYPE> &);

    void remove(TYPE);

    bool find(TYPE);

    std::size_t size() const;

    std::vector<TYPE> to_array() const;

    ~Tree();
};


template<typename TYPE>
Tree<TYPE>::Tree() {
    this->head = nullptr;
}


template<typename TYPE>
Tree<TYPE>::~Tree() {
    destroyTree(this->head);
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
*   Helper method for to_array. Will add an element into the vector
*/
template<typename TYPE>
Node<TYPE>* Tree<TYPE>::remove_node(Node<TYPE>* node, TYPE value) {
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
std::size_t Tree<TYPE>::count_nodes(Node<TYPE> *node) const {
    if (node == nullptr) {
        return 0;
    }

    return 1 + count_nodes(node->right) + count_nodes(node->left);
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
*   Method to insert an array into the tree
*/
template<typename TYPE>
void Tree<TYPE>::insert(std::vector<TYPE> &array) {
    for (auto value : array) {
        this->insert(value);
    }
}

/*
*   Method to remove an element
*/
template<typename TYPE>
void Tree<TYPE>::remove(TYPE value) {
    head = remove_node(head, value);
}


/*
*   Method to find an element
*/
template<typename TYPE>
bool Tree<TYPE>::find(TYPE value) {
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
std::size_t Tree<TYPE>::size() const {
    return count_nodes(this->head);
}


/*
*   Method to interpret tree as array
*/
template<typename TYPE>
std::vector<TYPE> Tree<TYPE>::to_array() const {
    std::vector<TYPE> result;
    to_array_helper(this->head, result);
    return result;
}