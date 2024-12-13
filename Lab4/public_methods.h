//
// Created by Andrii Zhupanov on 18.11.2024.
//

#ifndef PUBLIC_METHODS_H
#define PUBLIC_METHODS_H
#include "fstream"
#include "RedBlackTree.h"

template <typename T>
RedBlackTree<T>::RedBlackTree(Comparator cmp) : root(nullptr),size(0), nextIndex(0), cmp(cmp) {}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    clear();
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::search(const T& key) const {
    Node* current = root;
    while (current) {
        if (cmp(key, current->data)) {
            return current;
        } else if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename T>
void RedBlackTree<T>::insert(const T& data){
    Node* z = new Node(data, nextIndex++);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (cmp(data, x->data)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (cmp(data, y->data)) {
        y->left = z;
    } else {
        y->right = z;
    }

    size++;
    insertFixup(z);
}

template <typename T>
void RedBlackTree<T>::clear() {
    clear(root);
    root = nullptr;
    size = 0;
    nextIndex = 0;
}

template <typename T>
int RedBlackTree<T>::height() const {
    return height(root);
}

template <typename T>
void RedBlackTree<T>::toString() const {
    std::cout << "redblacktree:\nsize:" << size << "\n{\n";
    printPreOrder(root);
    std::cout << "}";
}

template <typename T>
void RedBlackTree<T>::printPreOrder() const {
    printPreOrder(root);
}


template <typename T>
void RedBlackTree<T>::printInOrder() const {
    printInOrder(root);
}

template <typename T>
void RedBlackTree<T>::toDot(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for writing DOT representation.");
    }

    outFile << "digraph RedBlackTree {\n";
    outFile << "    node [shape=circle, style=filled, fontcolor=white];\n";

    std::function<void(Node*)> writeNode = [&](Node* node) {
        if (!node) return;

        std::string color = (node->color == RED) ? "red" : "black";
        outFile << "    " << node->index << " [label=\"" << node->data << "\", fillcolor=" << color << "];\n";

        if (node->left) {
            outFile << "    " << node->index << " -> " << node->left->index << ";\n";
            writeNode(node->left);
        }
        if (node->right) {
            outFile << "    " << node->index << " -> " << node->right->index << ";\n";
            writeNode(node->right);
        }
    };

    if (root) {
        writeNode(root);
    }

    outFile << "}\n";
    outFile.close();
}
#endif //PUBLIC_METHODS_H
