//
// Created by Andrii Zhupanov on 04.11.2024.
//

#ifndef PRIVATE_METHOD_H
#define PRIVATE_METHOD_H

#include "BST.h"
#include <fstream>

template <class T>
void BinaryTree<T>::add(Node** node, const T& val)
{
    if (*node == nullptr)
    {
        *node = new Node{val, nullptr, nullptr};
        treeSize++;
    }
    else if (cmp(val, (*node)->value))
    {
        add(&(*node)->left, val);
    }
    else
    {
        add(&(*node)->right, val);
    }
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::find(Node* node, const T& val) const
{
    if (node == nullptr || node->value == val)
        return node;
    if (cmp(val, node->value))
        return find(node->left, val);
    else
        return find(node->right, val);
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMin(Node* node) const
{
    while (node && node->left)
        node = node->left;
    return node;
}

template <class T>
void BinaryTree<T>::remove(Node*& node, const T& val)
{
    if (node == nullptr)
        return;

    if (cmp(val, node->value))
    {
        remove(node->left, val);
    }
    else if (cmp(node->value, val))
    {
        remove(node->right, val);
    }
    else
    {
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else
        {
            Node* minRight = findMin(node->right);
            node->value = minRight->value;
            remove(node->right, minRight->value);
        }
        treeSize--;
    }
}

template <class T>
void BinaryTree<T>::printPreOrder(Node* node) const
{
    if (node != nullptr)
    {
        std::cout << node->value << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

template <class T>
void BinaryTree<T>::printInOrder(Node* node) const
{
    if (node != nullptr)
    {
        printInOrder(node->left);
        std::cout << node->value << " ";
        printInOrder(node->right);
    }
}

template <class T>
void BinaryTree<T>::deleteTree(Node* node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <class T>
int BinaryTree<T>::calculateHeight(Node* node) const
{
    if (node == nullptr)
        return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

template <class T>
void BinaryTree<T>::buildString(Node* node, int depth) const
{
    if (node)
    {
        std::cout << std::string(depth * 2, ' ') << "Node(" << node->value << "):\n";
        if (node->left)
            std::cout << std::string(depth * 2 + 2, ' ') << "L->" << node->left->value << "\n";
        else
            std::cout << std::string(depth * 2 + 2, ' ') << "L->NULL\n";
        if (node->right)
            std::cout << std::string(depth * 2 + 2, ' ') << "R->" << node->right->value << "\n";
        else
            std::cout << std::string(depth * 2 + 2, ' ') << "R->NULL\n";

        buildString(node->left, depth + 1);
        buildString(node->right, depth + 1);
    }
}

template <class T>
void BinaryTree<T>::toDot(Node* node, std::ofstream& out){
    if (!node) {
        return;
    }

    out << "  " << node->value << ";\n";

    if (node->left) {
        out << "  " << node->value << " -> " << node->left->value << ";\n";
        toDot(node->left, out);
    }

    if (node->right) {
        out << "  " << node->value << " -> " << node->right->value << ";\n";
        toDot(node->right, out);
    }
}

#endif //PRIVATE_METHOD_H
