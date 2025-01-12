//
// Created by Andrii Zhupanov on 27.12.2024.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "DynamicTable.h"

class UnionFind {
private:
  DynamicTable<int> parent;
  DynamicTable<int> rank;
  int findCount;

public:
  UnionFind(int n) : findCount(0) {
    for (int i = 0; i < n; i++) {
      parent.append(i);
      rank.append(0);
    }
  }

  int findPC(int x) {
    findCount++;
    if (parent.find(x) != x) {
      parent.change(x, findPC(parent.find(x)));
    }
    return parent.find(x);
  }

  int find(int x) {
    findCount++;
    while (x != parent.find(x)) {
      x = parent.find(x);
    }
    return x;
  }

  void unionByRank(int x, int y) {
    int rootX = findPC(x);
    int rootY = findPC(y);

    if (rootX != rootY) {
      if (rank.find(rootX) < rank.find(rootY)) {
        std::swap(rootX, rootY);
      }
      parent.change(rootY, rootX);
      if (rank.find(rootX) == rank.find(rootY)) {
        rank.change(rootX, rank.find(rootX) + 1);
      }
    }
  }

  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
      parent.change(rootY, rootX);
    }
  }

  int getFindCount() const {
    return findCount;
  }

  void resetFindCount() {
    findCount = 0;
  }
};

#endif // UNIONFIND_H
