//
// Created by Andrii Zhupanov on 04.11.2024.
//

#include <iostream>
#include <ctime>
#include "BST.h"

int generateRandomInt(const int min = 0, const int max = 10000000) {
    return rand() % (max - min + 1) + min;
}

template <typename T>
void test_time_and_report(BinaryTree<T>& tree) {
    for (int i = 1; i <= 7; ++i) {
        int hits = 0;
        int elements = pow(10, i);

        clock_t startInsert = clock();
        for (int j = 0; j < elements; ++j) {
            tree.add(generateRandomInt());
        }
        clock_t endInsert = clock();
        double insertTime = static_cast<double>(endInsert - startInsert) / CLOCKS_PER_SEC * 1000;
        double insertAvgTime = insertTime / elements;

        clock_t startSearch = clock();
        for (int j = 0; j < elements; ++j) {
            if(tree.find(generateRandomInt())) {
                hits++;
            };
        }
        clock_t endSearch = clock();
        double searchTime = static_cast<double>(endSearch - startSearch) / CLOCKS_PER_SEC * 1000;
        double searchAvgTime = searchTime / elements;

        int treeHeight = tree.height();
        double logSize = log2(elements);
        double heightToSize = static_cast<double>(treeHeight) / elements;
        double heightToLogSize = static_cast<double>(treeHeight) / logSize;

        std::cout <<"Size\t" << elements << "\n"
                  <<"Hits\t" << hits << "\n"
                  <<"Height\t" << treeHeight << "\n"
                  <<"Height/Size\t" << heightToSize << "\n"
                  <<"Log2(Size)\t" << logSize << "\n"
                  <<"Height/Log2(Size)\t" << heightToLogSize << "\n"
                  <<"Insert(ms)\t" << insertTime << "\n"
                  <<"Insert Avg(ms)\t" << insertAvgTime << "\n"
                  <<"Search(ms)\t" << searchTime << "\n"
                  <<"Search Avg(ms)\t" << searchAvgTime << "\n\n";

        std::string fileName = "test" + std::to_string(elements) + ".dot";
        tree.toDot(fileName);
        if(elements == 10) {
            tree.printInOrder();
            std::cout << std::endl;
            tree.printPreOrder();
            std::cout << std::endl;
        }
        tree.clear();
    }
}

int main() {
    srand(time(nullptr));
    BinaryTree<int> tree;

    //Test method
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.toString();
    auto node = tree.find(10);
    if (node) std::cout << "Element 10 found in BST.\n";
    tree.remove(node);
    tree.toString();
    tree.clear();
    std::cout << std::endl << std::fixed;
    test_time_and_report(tree);
    return 0;
}
