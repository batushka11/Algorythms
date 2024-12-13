//
// Created by Andrii Zhupanov on 14.10.2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>
#include <stdexcept>
#include <string>

template <class T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void insertBegin(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        size++;
    }

    void insertEnd(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void deleteBegin() {
        if (head == nullptr) {
            return;
        }
        const Node<T>* curr = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        size--;
        delete curr;
    }

    void deleteEnd() {
        if (tail == nullptr) {
            return;
        }
        const Node<T>* curr = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        size--;
        delete curr;
    }

    int getSize() const {
        return size;
    }

    T getData(const int index) {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range");
        }
        Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    void printList() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* curr = head;
        std::cout << "List is: ";
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    void setData(const int index, const T& data) {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range");
        }
        Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        curr->data = data;
    }

    Node<T>* getNodeUsingComparator(std::function<bool(T)> comp) {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (comp(curr->data)) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void deleteNodeUsingComparator(std::function<bool(T)> comp) {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        Node<T>* deleteNode = getNodeUsingComparator(comp);

        if (deleteNode == nullptr) {
            return;
        }

        if (deleteNode == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            Node<T>* curr = head;
            while (curr != nullptr && curr->next != deleteNode) {
                curr = curr->next;
            }
            if (curr != nullptr) {
                curr->next = deleteNode->next;
                if (deleteNode->next != nullptr) {
                    deleteNode->next->prev = curr;
                }
            }
        }

        size--;
        delete deleteNode;
    }

    void insertInOrder(const T& data, std::function<bool(int, int)> comparator = std::less<int>()) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = tail = newNode;
        } else {
            Node<T>* current = head;
            while (current && comparator(current->data, data)) {
                current = current->next;
            }
            if (!current) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            } else if (!current->prev) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            } else {
                newNode->next = current;
                newNode->prev = current->prev;
                current->prev->next = newNode;
                current->prev = newNode;
            }
        }
        size++;
    }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    std::string toString(const int elementsToPrint = 0) {
        const int printCount = (elementsToPrint == 0) ? size : elementsToPrint;
        std::string result = "List size: " + std::to_string(size) + "\nElements: ";
        Node<T>* current = head;
        for (int i = 0; i < printCount && current; i++) {
            result += std::to_string(current->data) + " ";
            current = current->next;
        }
        if (printCount < size) {
            result += "... ";
        }
        return result;
    }
};

#endif
