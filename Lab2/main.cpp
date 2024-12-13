#include <iostream>
#include "cmake-build-debug/DynamicTable.h"
#include <cstdlib>
#include <ctime>

int generateRandomInt(const int min = 0, const int max = 10000) {
  return rand() % (max - min + 1) + min;
}

template <typename T>
void test_time(DynamicTable<T>*& my_table) {
  try {
    for (int i = 0; i < 5; i++) {
      std::cout << std::fixed << std::endl;
      const int elements = pow(10, i);
      double max_time_per_element = 0.0;
      int worst_index = -1;

      my_table = new DynamicTable<T>();
      const clock_t start = clock();
      for (int j = 0; j < elements; j++) {
        T data = generateRandomInt();
        const clock_t t1_element = clock();

        my_table->append(data);

        const clock_t t2_element = clock();
        double time_per_element = static_cast<double>(t2_element - t1_element) / CLOCKS_PER_SEC;

        if (time_per_element > max_time_per_element) {
          max_time_per_element = time_per_element;
          worst_index = j;
          std::cout << "New worst time: " << max_time_per_element << "ms at index " << worst_index << std::endl;
        }
      }
      const clock_t end = clock();

      const double total_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
      const double amortized_time = total_time / elements;

      std::cout << "Total time for " << elements << " elements: " << total_time << "ms" << std::endl;
      std::cout << "Amortized time per element: " << amortized_time << "ms" << std::endl;
      my_table->to_string();
      my_table->clear();
    }
  }
  catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
}


int main() {
  try {
    DynamicTable<int>* table = new DynamicTable<int>();

    //Test append item
    table->append(13);
    table->append(61);
    table->append(32);
    table->append(47);
    table->append(92);

    //Test to string
    table->to_string();

    //Test find item
    const int search_item = table->find(2);
    std::cout << "Search item: " << search_item << std::endl;

    //Test change item
    table->change(4, 101);
    std::cout << "Change item: " << table->find(4) << std::endl;

    //Test bubble sort
    table->bubble_sort();
    table->to_string();

    table->clear();

    test_time(table);
  }
  catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
  catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
}
