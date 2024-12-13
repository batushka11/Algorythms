//
// Created by Andrii Zhupanov on 14.10.2024.
//
#include "LinkedList.h"

#include <cstdlib>
#include <ctime>
#include <iomanip>

int generateRandomInt(const int min = 0, const int max = 10000) {
    return rand() % (max - min + 1) + min;
}

template <typename T>
void test_time(List<T> myList) {
    try {
        for(int i = 0; i < 5; i++) {
            const int elements = pow(10,i);
            clock_t start = clock();
            for(int i = 0; i < elements; i++) {
                myList.insertBegin(generateRandomInt());
            }
            clock_t end = clock();
            double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
            std::cout<< time << "ms for insert random data in " << elements << " elements list" <<std::endl;
            std::cout << time/elements << "ms average for insert random data in " << elements << " elements list" <<std::endl;
            start = clock();
            for(int i = 0; i < elements; i++) {
                myList.deleteNodeUsingComparator([](const int x) { return x == generateRandomInt(); });
            }
            end = clock();
            time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
            std::cout << time << "ms for delete random data in " << elements <<" elements list" <<std::endl;
            std::cout << std::fixed << std::setprecision(10) << (time/elements) << "ms average for delete random data in " << elements << " elements list\n" <<std::endl;
            myList.clear();
        }
    }
    catch(const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

int main() {
    try {
        List<int> myList;

        myList.insertBegin(10);
        myList.insertEnd(200);
        myList.insertEnd(30);
        myList.insertEnd(25);
        myList.insertEnd(35);

        std::cout << "Size after insertions: " << myList.getSize() << std::endl;
        myList.printList();
        std::cout << std::endl;

        myList.deleteBegin();
        std::cout << "Size after deleting from beginning: " << myList.getSize() << std::endl;
        myList.printList();
        std::cout << std::endl;

        myList.deleteEnd();
        std::cout << "Size after deleting from end: " << myList.getSize() << std::endl;
        myList.printList();
        std::cout << std::endl;

        const int elem = myList.getData(1);
        std::cout << "Data on first index: " << elem << std::endl;

        myList.setData(2, 100);
        myList.printList();
        std::cout << std::endl;

        const Node<int> *result = myList.getNodeUsingComparator([](const int x) { return x == 200; });
        std::cout << "Element found: " << result << std::endl;

        myList.deleteNodeUsingComparator([](const int x) { return x == 200; });
        myList.printList();
        std::cout << std::endl;

        myList.printList();
        myList.insertInOrder(15);
        myList.insertInOrder(40);
        myList.insertInOrder(5);
        std::cout << "List after inserting in order (5, 15, 40):" << std::endl;
        myList.printList();
        std::cout << std::endl;

        myList.clear();
        std::cout << "Size after clearing the list: " << myList.getSize() << std::endl;
        try {
            myList.printList();
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }

        myList.insertEnd(50);
        myList.insertEnd(60);
        myList.insertEnd(70);
        std::cout << myList.toString(2) << "\n" << std::endl;
        myList.clear();

        test_time(myList);
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

  return 0;
}


