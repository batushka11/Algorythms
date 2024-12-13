//
// Created by Andrii Zhupanov on 04.11.2024.
//

#ifndef PUBLIC_METHOD_H
#define PUBLIC_METHOD_H

#include "BST.h"
#include <fstream>

template <class T>
BinaryTree<T>::BinaryTree(Comparator cmp) : root(nullptr), treeSize(0), cmp(cmp) {}

template <class T>
BinaryTree<T>::~BinaryTree()
{
  clear();
}

template <class T>
int BinaryTree<T>::size() const
{
  return treeSize;
}

template <class T>
void BinaryTree<T>::add(const T& val)
{
  add(&root, val);
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::find(const T& val) const
{
  return find(root, val);
}

template <class T>
void BinaryTree<T>::remove(Node* targetNode)
{
  if (targetNode)
  {
    remove(root, targetNode->value);
  }
}

template <class T>
void BinaryTree<T>::printPreOrder()
{
  printPreOrder(root);
  std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder()
{
  printInOrder(root);
  std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::clear()
{
  deleteTree(root);
  root = nullptr;
  treeSize = 0;
}

template <class T>
int BinaryTree<T>::height() const
{
  return calculateHeight(root);
}

template <class T>
void BinaryTree<T>::toString() const
{
  buildString(root);
}

template <class T>
void BinaryTree<T>::toDot(const std::string& filename){
  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Error opening file: " << filename << "\n";
    return;
  }

  out << "digraph BST {\n";
  toDot(root, out);
  out << "}\n";

  out.close();
}

#endif //PUBLIC_METHOD_H
