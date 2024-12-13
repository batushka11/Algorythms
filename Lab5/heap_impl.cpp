//
// Created by Andrii Zhupanov on 25.11.2024.
//

#include "heap.h"
#include <iostream>

template<typename T>
binary_heap<T>::binary_heap(int initial_capacity) : size(0), capacity(initial_capacity) {
  data = new T[capacity];
}

template<typename T>
binary_heap<T>::~binary_heap() {
  delete[] data;
}

template<typename T>
void binary_heap<T>::resize() {
  capacity *= 2;
  T* new_data = new T[capacity];

  for (int i = 0; i < size; i++) {
    new_data[i] = data[i];
  }

  delete[] data;
  data = new_data;
}


template<typename T>
void binary_heap<T>::add(const T& element, std::function<bool(const T&, const T&)> comparator) {
  if (size == capacity) {
    resize();
  }

  data[size] = element;
  heapify_up(size, comparator);
  size++;
}

template<typename T>
T binary_heap<T>::poll(std::function<bool(const T&, const T&)> comparator) {
  if (size == 0) {
    throw std::out_of_range("Heap is empty");
  }

  T root = data[0];
  data[0] = data[size - 1];
  size--;
  heapify_down(0, comparator);
  return root;
}

template<typename T>
void binary_heap<T>::heapify_up(int index, std::function<bool(const T&, const T&)> comparator) {
  int parent = (index - 1) / 2;

  while (index > 0 && comparator(data[index], data[parent])) {
    std::swap(data[index], data[parent]);
    index = parent;
    parent = (index - 1) / 2;
  }
}

template<typename T>
void binary_heap<T>::heapify_down(int index, std::function<bool(const T&, const T&)> comparator) {
  int largest = index;

  while (true) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && comparator(data[left], data[largest])) {
      largest = left;
    }
    if (right < size && comparator(data[right], data[largest])) {
      largest = right;
    }

    if (largest != index) {
      std::swap(data[index], data[largest]);
      index = largest;
    } else {
      break;
    }
  }
}

template<typename T>
void binary_heap<T>::clear() {
  delete[] data;
  data = new T[capacity];
  size = 0;
}


template<typename T>
void binary_heap<T>::to_string() const {
  for (int i = 0; i < size; i++) {
    std::cout << data[i];
    if (i < size - 1) {
      std::cout << ",";
    }
  }
  std::cout << std::endl;
}


template class binary_heap<int>;