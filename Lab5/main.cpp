//
// Created by Andrii Zhupanov on 25.11.2024.
//

#include <iostream>
#include <ctime>
#include "heap.h"

int generateRandomInt(const int min = 0, const int max = 100000) {
  return rand() % (max - min + 1) + min;
}

void test() {
    const int MAX_ORDER = 7;
    binary_heap<int> bh;

    for (int o = 4; o <= MAX_ORDER; o++) {
        int n = std::pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            bh.add(generateRandomInt(), [](int a, int b) { return a > b; });
        }
        clock_t t2 = clock();
        std::cout << std::fixed << "Adding " << n << " elements took " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms(total).\n";
        std::cout << std::fixed << "Adding " << n << " elements took " << (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000) / n << " ms(average).\n";

        t1 = clock();
        for (int i = 0; i < 1000; i++) {
            bh.poll([](int a, int b) { return a > b; });
        }
        t2 = clock();
        std::cout << std::fixed << "Removing " << n << " elements took " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms(total).\n";
        std::cout << std::fixed << "Removing " << n << " elements took " << (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000) / n << " ms(average).\n";
        bh.clear();
        std::cout << std::endl;
    }
}
int main() {
    test();
    return 0;
}
