//
// Created by Andrii Zhupanov on 26.10.2024.
//

#ifndef DYNAMICTABLE_H
#define DYNAMICTABLE_H

#include <iostream>

template <typename T>
class DynamicTable {
private:
  T *table;
  int current_size;
  int max_size;
  double factor;

public:
  DynamicTable(double factor = 2.0) :
  table(new T[1]), current_size(0), max_size(1), factor(factor) {
    if(factor <= 1.0) {
      throw std::invalid_argument("Factor must be greater than one");
    }
  };
  ~DynamicTable(){clear();}

  void append(T item) {
    if (current_size == max_size) {
            max_size = (max_size * factor);
            T* newTable = new T[max_size];
            for (int i = 0; i < current_size; i++) {
                newTable[i] = table[i];
            }
            delete[] table;
            table = newTable;
        }
        table[current_size++] = item;
  }
  int get_size() {
    return current_size;
  }
  T find(int index) {
    if(index >= 0 && index < current_size) {
      return table[index];
    }
    throw std::out_of_range("Index out of range");
  }

  void change(int index, T item) {
    if(index >= 0 && index < current_size) {
      table[index] = item;
      return;
    }
    throw std::out_of_range("Index out of range");
  }

  void clear() {
    delete [] table;
    current_size = 0;
    max_size = 1;
    table = new T[1];
  }

  void to_string() {
    std::cout << "Table current size:" << current_size << std::endl;
    std::cout << "Table max size:" << max_size << std::endl;
    std::cout << "Table elements:" << std::endl;
    for (int i = 0; i < current_size; i++) {
      std::cout << table[i] << " ";
    }
    std::cout << std::endl;
  }

  void bubble_sort(std::function<bool(T, T)> comparator = std::less<T>()) {
    for (int i = 0; i < current_size - 1; i++) {

      bool flag = false;
      for (int j = 0; j < current_size - i - 1; j++) {
        if (comparator(table[j + 1], table[j])) {
          std::swap(table[j], table[j + 1]);

          flag = true;
        }
      }

      if (!flag)
        break;
    }
  }


  const T& find(int index) const {
    if (index < 0 || index >= current_size) {
      throw std::out_of_range("Index out of range");
    }
    return table[index];
  }

  T* begin() { return table; }
  T* end() { return table + current_size; }

  const T* begin() const { return table; }
  const T* end() const { return table + current_size; }
};
#endif

