//
// Created by Andrii Zhupanov on 08.12.2024.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include "LinkedList.h"

template <typename V>
class HashTable {
private:
    struct HashEntry {
        std::string key;
        V value;
        HashEntry(const std::string& k, const V& v) : key(k), value(v) {}
    };

    List<HashEntry>* table;
    int size;
    int capacity;
    const double loadFactor = 0.75;

    int hash(const std::string& key) const {
        int hash = 0;
        int p = 31;
        for (char c : key) {
            hash = (hash * p + c) % capacity;
        }
        return hash < 0 ? hash + capacity : hash;
    }

    void rehash() {
        int oldCapacity = capacity;
        auto oldTable = table;
        capacity *= 2;
        table = new List<HashEntry>[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = List<HashEntry>();
        }
        size = 0;
        for (int i = 0; i < oldCapacity; ++i) {
            while (oldTable[i].getSize() > 0) {
                HashEntry entry = oldTable[i].getData(0);
                put(entry.key, entry.value);
                oldTable[i].deleteBegin();
            }
        }
        delete[] oldTable;
    }

public:
    HashTable(int initialCapacity = 16) : size(0), capacity(initialCapacity) {
        table = new List<HashEntry>[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = List<HashEntry>();
        }
    }

    ~HashTable() {
        clear();
        delete[] table;
    }

    void put(const std::string& key, const V& value) {
        int idx = hash(key);
        Node<HashEntry>* entryNode = table[idx].getNodeUsingComparator(
            [&](HashEntry entry) { return entry.key == key; });
        if (entryNode) {
            entryNode->data.value = value;
        } else {
            table[idx].insertEnd(HashEntry(key, value));
            ++size;
            if ((double)size / capacity > loadFactor) {
                rehash();
            }
        }
    }

    V* get(const std::string& key) {
        int idx = hash(key);
        Node<HashEntry>* entryNode = table[idx].getNodeUsingComparator(
            [&](HashEntry entry) { return entry.key == key; });
        if (entryNode) {
            return &entryNode->data.value;
        }
        return nullptr;
    }

    bool remove(const std::string& key) {
        int idx = hash(key);
        Node<HashEntry>* entryNode = table[idx].getNodeUsingComparator(
            [&](HashEntry entry) { return entry.key == key; });
        if (entryNode) {
            table[idx].deleteNodeUsingComparator(
                [&](HashEntry entry) { return entry.key == key; });
            --size;
            return true;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < capacity; ++i) {
            table[i].clear();
        }
        size = 0;
    }

    void to_string() {
        std::cout << "table:\n{\n";
        for (int i = 0; i < capacity; ++i) {
            if (table[i].getSize() > 0) {
                std::cout << i << ":";
                bool firstEntry = true;
                for (int j = 0; j < table[i].getSize(); ++j) {
                    HashEntry entry = table[i].getData(j);
                    if (!firstEntry) {
                        std::cout << ",";
                    }
                    std::cout << entry.key << "->" << entry.value;
                    firstEntry = false;
                }
                std::cout << ";\n";
            }
        }
        std::cout << "}\n";
    }

    void printStats() const {
        int nonEmptyChains = 0, maxChainLength = 0;
        int minChainLength = std::numeric_limits<int>::max();;
        double totalLength = 0;

        for (int i = 0; i < capacity; ++i) {
            int chainLength = table[i].getSize();
            if (chainLength > 0) {
                ++nonEmptyChains;
                maxChainLength = std::max(maxChainLength, chainLength);
                minChainLength = std::min(minChainLength, chainLength);
                totalLength += chainLength;
            }
        }
        double avgLength = nonEmptyChains ? totalLength / nonEmptyChains : 0;

        if (nonEmptyChains == 0) {
            minChainLength = 0;
        }

        std::cout << "stats:\n";
        std::cout << "list min size:" << minChainLength << "\n";
        std::cout << "list max size:" << maxChainLength << "\n";
        std::cout << "non-null lists:" << nonEmptyChains << "\n";
        std::cout << "list avg size:" << avgLength << "\n";
        std::cout << "load factor:" << (double)size / capacity << "\n";
    }

};

#endif
