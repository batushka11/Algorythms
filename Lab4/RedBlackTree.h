//
// Created by Andrii Zhupanov on 18.11.2024.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <functional>

enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
  struct Node {
    T data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
    int index;

    Node(T value, int idx)
        : data(value), parent(nullptr), left(nullptr), right(nullptr), color(RED), index(idx) {}
  };
public:
  using Comparator = std::function<bool(const T&, const T&)>;
  RedBlackTree(Comparator cmp = [](const T& a, const T& b) { return a < b; });
  ~RedBlackTree();

  Node* search(const T& key) const;
  void insert(const T& data);
  void clear();
  int height() const;
  void toString() const;
  void printPreOrder() const;
  void printInOrder() const;
  void toDot(const std::string& fileName) const;
private:
  Node* root;
  int size;
  int nextIndex;
  Comparator cmp;

  void leftRotate(Node* x);
  void rightRotate(Node* x);
  void insertFixup(Node* z);
  void clear(Node* node);
  void printPreOrder(Node* node) const;
  void printInOrder(Node* node) const;
  int height(Node* node) const;
};

#include "private_methods.h"
#include "public_methods.h"
#endif

