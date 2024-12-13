//
// Created by Andrii Zhupanov on 18.11.2024.
//

#ifndef PRIVATE_METHODS_H
#define PRIVATE_METHODS_H
#include "RedBlackTree.h"

template <typename T>
void RedBlackTree<T>::leftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left) y->left->parent = x;
  y->parent = x->parent;
  if (!x->parent) root = y;
  else if (x == x->parent->left) x->parent->left = y;
  else x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rightRotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right) y->right->parent = x;
  y->parent = x->parent;
  if (!x->parent) root = y;
  else if (x == x->parent->right) x->parent->right = y;
  else x->parent->left = y;
  y->right = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::insertFixup(Node* z) {
  while (z->parent && z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      Node* y = z->parent->parent->right;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(z->parent->parent);
      }
    } else {
      Node* y = z->parent->parent->left;
      if (y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename T>
int RedBlackTree<T>::height(Node* node) const {
  if (!node) return 0;
  return 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
void RedBlackTree<T>::printInOrder(Node* node) const {
  if (node) {
    printInOrder(node->left);
    std::cout << "(" << node->data << ":" << (node->color == RED ? "R" : "B") << "), ";
    printInOrder(node->right);
  }
}

template <typename T>
void RedBlackTree<T>::printPreOrder(Node* node) const {
  if (node) {
    std::cout << "(" << node->data << ":" << (node->color == RED ? "R" : "B") << "), ";
    printPreOrder(node->left);
    printPreOrder(node->right);
  }
}

#endif //PRIVATE_METHODS_H
