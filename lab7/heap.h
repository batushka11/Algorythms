//
// Created by Andrii Zhupanov on 25.11.2024.
//

#ifndef HEAP_H
#define HEAP_H
#include <functional>

template<typename T>
class binary_heap {
private:
  T* data;
  int size;
  int capacity;
  bool ownMemory;

  void resize();
  void heapify_up(int index, std::function<bool(const T&, const T&)> comparator);
  void heapify_down(int index, std::function<bool(const T&, const T&)> comparator);

public:
  binary_heap(int initial_capacity = 16);
  binary_heap(T* array, int array_size, bool use_bottom_up, std::function<bool(const T&, const T&)> comparator);
  ~binary_heap();

  void add(const T& element, std::function<bool(const T&, const T&)> comparator);
  T poll(std::function<bool(const T&, const T&)> comparator);
  void clear();
  void to_string() const;

  void heapify_top_down(std::function<bool(const T&, const T&)> comparator);
  void heapify_bottom_up(std::function<bool(const T&, const T&)> comparator);
  static void sort(T* array, int array_size,bool use_bottom_up, std::function<bool(const T&, const T&)> comparator);
};

#endif //HEAP_H
