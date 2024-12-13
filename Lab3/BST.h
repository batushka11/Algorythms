//
// Created by Andrii Zhupanov on 04.11.2024.
//
#ifndef BST_H
#define BST_H

#include <iostream>

template <class T>
class BinaryTree
{
    struct Node
    {
        T value;
        struct Node* right;
        struct Node* left;
    };

public:
    using Comparator = std::function<bool(const T&, const T&)>;
    BinaryTree(Comparator cmp = [](const T& a, const T& b) { return a < b; });
    ~BinaryTree();

    void add(const T& val);
    Node* find(const T& val) const;
    void remove(Node* targetNode);
    void printPreOrder();
    void printInOrder();
    int size() const;
    void clear();
    int height() const;
    void toString() const;
    void toDot(const std::string& filename);

private:
    Node* root;
    int treeSize;
    Comparator cmp;

    void add(Node** node, const T& val);
    Node* find(Node* node, const T& val) const;
    Node* findMin(Node* node) const;
    void remove(Node*& node, const T& val);
    void printPreOrder(Node* node) const;
    void printInOrder(Node* node) const;
    void deleteTree(Node* node);
    int calculateHeight(Node* node) const;
    void buildString(Node* node, int depth = 0) const;
    void toDot(Node* node, std::ofstream& out);
};

#include "private_method.h"
#include "public_method.h"
#endif
