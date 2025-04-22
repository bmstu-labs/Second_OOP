#pragma once

#include <memory>
#include <stack>
#include <stdexcept>

#include "tree.hpp"


template<typename TYPE>
class Tree;

template<typename TYPE>
class Iterator {
    friend class Tree<TYPE>;
private:
    node_ptr<TYPE> current;

    std::stack<node_ptr<TYPE>> nodes;

    const Tree<TYPE> &tree_ref;

private:
    void push_left(node_ptr<TYPE>);

    void mark_as_end();
public:
    explicit Iterator(const Tree<TYPE> &);

    Iterator<TYPE> next();

    TYPE value() const;

    bool is_end() const;

    Iterator<TYPE> &operator ++ ();

    TYPE &operator * () const;

    bool operator == (const Iterator<TYPE> &);

    bool operator != (const Iterator<TYPE> &);
};


template<typename TYPE>
Iterator<TYPE>::Iterator(const Tree<TYPE> &tree) : tree_ref(tree) {
    auto root = tree.get_root();
    if (root) {
        this->push_left(root);
        this->current = this->nodes.empty() ? nullptr : this->nodes.top();
    }
}

template<typename TYPE>
Iterator<TYPE> Iterator<TYPE>::next() {
    Iterator<TYPE> temp = *this;
    ++(*this);
    return temp;
}

template<typename TYPE>
TYPE Iterator<TYPE>::value() const {
    if (!this->current) {
        throw std::runtime_error("Iterator is at end");
    }
    return this->current->get_value();
}

template<typename TYPE>
bool Iterator<TYPE>::is_end() const {
    return this->current == nullptr;
}

template<typename TYPE>
Iterator<TYPE> &Iterator<TYPE>::operator ++ () {
    if (this->nodes.empty()) {
        this->current = nullptr;
    } 
    
    else {
        this->current = this->nodes.top();
        this->nodes.pop();
        if (this->current->right) {
            this->push_left(this->current->right);
        }
    }

    return *this;
}

template<typename TYPE>
TYPE &Iterator<TYPE>::operator * () const {
    if (!this->current) {
        throw std::runtime_error("Dereferencing end iterator");
    }

    return this->current;
}

template<typename TYPE>
bool Iterator<TYPE>::operator == (const Iterator<TYPE> &other) {
    return &this->tree_ref == &other.tree_ref && this->current == other.current;
}

template<typename TYPE>
bool Iterator<TYPE>::operator!=(const Iterator<TYPE>& other) {
    return !(*this == other);
}

template<typename TYPE>
void Iterator<TYPE>::push_left(node_ptr<TYPE> node) {
    while (node) {
        this->nodes.push(node);
        node = node->left;
    }
}

template<typename TYPE>
void Iterator<TYPE>::mark_as_end() {
    this->current = nullptr;
    while (!nodes.empty()) {
        nodes.pop();
    }
}