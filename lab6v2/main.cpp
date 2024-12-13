//
// Created by Andrii Zhupanov on 08.12.2024.
//

#include <iostream>
#include <ctime>
#include "hash_table.h"

std::string generateRandomString(size_t length = 6) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t charset_size = sizeof(charset) - 1;
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += charset[rand() % charset_size];
    }
    return result;
}

void testHashTable() {
    const int MAX_ORDER = 7;
    HashTable<int> ht;

    for (int o = 4; o <= MAX_ORDER; ++o) {
        int n = std::pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; ++i) {
            ht.put(generateRandomString(6), i);
        }
        clock_t t2 = clock();
        std::fixed;
        std::cout << "Inserting " << n << " elements took "
                  << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms (total).\n";
        std::cout << "Inserting " << n << " elements took "
                  << (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000) / n << " ms (average).\n";

        const int m = 10000;
        t1 = clock();
        for (int i = 0; i < m; ++i){
            ht.get(generateRandomString(6));
        }
        t2 = clock();
        std::cout << "Retrieving " << m << " random elements took "
                  << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms (total).\n";
        std::cout << "Retrieving " << m << " random elements took "
                  << (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000) / m << " ms (average).\n";

        ht.printStats();
        ht.clear();
        std::cout << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    testHashTable();
    return 0;
}
