#pragma once

#include <iostream>
#include <vector>

template<typename TYPE>
class Node {
public:
    TYPE data;
    Node *left;
    Node *right;

    Node();

    Node(TYPE);
};

template<typename TYPE>
Node<TYPE>::Node() {
    data = TYPE{};
    left = nullptr;
    right = nullptr;
}

template<typename TYPE>
Node<TYPE>::Node(TYPE value) {
    data = value;
    left = nullptr;
    right = nullptr; 
}