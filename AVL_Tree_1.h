#pragma once

#include <memory>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "wet1util.h"

using std::unique_ptr;
using std::make_unique;

template <typename T>
struct Node {
    int key;
    T data;
    int height = 1;
    unique_ptr<Node<T>> left = nullptr;
    unique_ptr<Node<T>> right = nullptr;

    Node(int key, T data) : key(key), data(data) {};
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

template <typename T>
class AVL_Tree {
private:
    unique_ptr<Node<T>> head = nullptr;

    int getHeight(Node<T>* node) const;
    int getBalance(Node<T>* node) const;
    Node<T>* Find_Next(Node<T>* node);

    StatusType insert_rec(unique_ptr<Node<T>>& node, const int& insert_key, const T& data);
    StatusType Remove_rec(unique_ptr<Node<T>>& node, const int& key);

    unique_ptr<Node<T>> LeftRotate(unique_ptr<Node<T>> node);
    unique_ptr<Node<T>> RightRotate(unique_ptr<Node<T>> node);

    std::unique_ptr<Node<T>> copy_rec(Node<T>* source_node);


public:
    AVL_Tree() = default;
    ~AVL_Tree() = default;
    AVL_Tree(const AVL_Tree& other);
    //AVL_Tree(const AVL_Tree&) = delete;
    AVL_Tree& operator=(const AVL_Tree&) = delete;

    StatusType Insert(const int& key, const T& data);
    StatusType Remove(const int& key);
    output_t<T*> Find(const int& key)const;

};

template <typename T>
int AVL_Tree<T>::getHeight(Node<T>* node) const {
    if (node == nullptr){
        return 0;
    }
    return node->height;
}

template <typename T>
int AVL_Tree<T>::getBalance(Node<T>* node) const {
    if (node == nullptr){
        return 0;
    }
    return getHeight(node->left.get()) - getHeight(node->right.get());
}

template <typename T>
Node<T>* AVL_Tree<T>::Find_Next(Node<T>* node) {
    while (node->left != nullptr) {
        node = node->left.get();
    }
    return node;
}

template <typename T>
unique_ptr<Node<T>> AVL_Tree<T>::RightRotate(unique_ptr<Node<T>> node) {
    unique_ptr<Node<T>> new_root = std::move(node->left);
    node->left = std::move(new_root->right);
    new_root->right = std::move(node);

    new_root->right->height = 1 + std::max(getHeight(new_root->right->left.get()), getHeight(new_root->right->right.get()));
    new_root->height = 1 + std::max(getHeight(new_root->left.get()), getHeight(new_root->right.get()));

    return new_root;
}

template <typename T>
unique_ptr<Node<T>> AVL_Tree<T>::LeftRotate(unique_ptr<Node<T>> node) {
    unique_ptr<Node<T>> new_root = std::move(node->right);
    node->right = std::move(new_root->left);
    new_root->left = std::move(node);

    new_root->left->height = 1 + std::max(getHeight(new_root->left->left.get()), getHeight(new_root->left->right.get()));
    new_root->height = 1 + std::max(getHeight(new_root->left.get()), getHeight(new_root->right.get()));

    return new_root;
}



template <typename T>
StatusType AVL_Tree<T>::insert_rec(unique_ptr<Node<T>>& node, const int& insert_key, const T& data) {

    if (node == nullptr) {
        try {
            node = make_unique<Node<T>>(insert_key, data);
        } catch (const std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
    }
    if (insert_key == node->key) {
        return StatusType::FAILURE;
    }

    StatusType res;
    if (insert_key < node->key) {
        res = insert_rec(node->left, insert_key, data);
    } else {
        res = insert_rec(node->right, insert_key, data);
    }

    if (res != StatusType::SUCCESS) {
        return res;
    }

    node->height = 1 + std::max(getHeight(node->left.get()), getHeight(node->right.get()));
    int balance = getBalance(node.get());

    // LL
    if (balance > 1 && insert_key < node->left->key) {
        node = RightRotate(std::move(node));
        return StatusType::SUCCESS;
    }
    // LR
    if (balance > 1 && insert_key > node->left->key) {
        node->left = LeftRotate(std::move(node->left));
        node = RightRotate(std::move(node));
        return StatusType::SUCCESS;
    }
    // RR
    if (balance < -1 && insert_key > node->right->key) {
        node = LeftRotate(std::move(node));
        return StatusType::SUCCESS;
    }
    // RL
    if (balance < -1 && insert_key < node->right->key) {
        node->right = RightRotate(std::move(node->right));
        node = LeftRotate(std::move(node));
        return StatusType::SUCCESS;
    }

    return StatusType::SUCCESS;
}

template <typename T>
StatusType AVL_Tree<T>::Remove_rec(unique_ptr<Node<T>>& node, const int& key) {

    if (node == nullptr) {
        return StatusType::FAILURE;
    }

    StatusType res;
    if (key < node->key) {
        res = Remove_rec(node->left, key);
    } else if (key > node->key) {
        res = Remove_rec(node->right, key);
    } else {

        //one child
        if (node->left == nullptr) {
            node = std::move(node->right);
            res = StatusType::SUCCESS;
        } else if (node->right == nullptr) {
            node = std::move(node->left);
            res = StatusType::SUCCESS;
        } else {
            // 2 children
            Node<T> *temp = Find_Next(node->right.get());
            node->key = temp->key;
            node->data = temp->data;
            //std::swap(node->data, temp->data);
            res = Remove_rec(node->right, temp->key);
        }
    }

    if (res != StatusType::SUCCESS) {
        return res;
    }
    if (node == nullptr) {
        return StatusType::SUCCESS;
    }
    node->height = 1 + std::max(getHeight(node->left.get()), getHeight(node->right.get()));
    int balance = getBalance(node.get());
    int left_balance = getBalance(node->left.get());
    int right_balance = getBalance(node->right.get());

    if (balance > 1) {
        // LL
        if (left_balance >= 0) {
            node = RightRotate(std::move(node));
        } else { // LR
            node->left = LeftRotate(std::move(node->left));
            node = RightRotate(std::move(node));
        }
    }
    else if (balance < -1) {
        // RR
        if (right_balance <= 0) {
            node = LeftRotate(std::move(node));
        } else { // RL
            node->right = RightRotate(std::move(node->right));
            node = LeftRotate(std::move(node));
        }
    }
    return StatusType::SUCCESS;
}


template <typename T>
StatusType AVL_Tree<T>::Insert(const int& key, const T& data) {
    if (key <=0 ){
        return StatusType::INVALID_INPUT;
    }
    return insert_rec(head, key, data);
}

template <typename T>
StatusType AVL_Tree<T>::Remove(const int& key) {
    if (key <=0 ){
        return StatusType::INVALID_INPUT;
    }
    return Remove_rec(head, key);
}

template <typename T>
output_t<T*> AVL_Tree<T>::Find(const int& key)const {
    Node<T>* info = head.get();
    while (info != nullptr) {
        if (key == info->key) {
            return output_t<T*>(&info->data);
        }
        if (key < info->key) {
            info= info->left.get();
        } else {
            info = info->right.get();
        }
    }
    return output_t<T*>(StatusType::FAILURE);
}

template <typename T>
std::unique_ptr<Node<T>> AVL_Tree<T>::copy_rec(Node<T>* source_node) {
    if (source_node == nullptr) {
        return nullptr;
    }
    auto new_node = std::make_unique<Node<T>>(source_node->key, source_node->data);
    new_node->height = source_node->height;
    new_node->left = copy_rec(source_node->left.get());
    new_node->right = copy_rec(source_node->right.get());
    return new_node;
}

template <typename T>
AVL_Tree<T>::AVL_Tree(const AVL_Tree& other) {
    head = copy_rec(other.head.get());
}
