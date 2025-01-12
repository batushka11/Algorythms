//
// Created by Andrii Zhupanov on 06.01.2025.
//

#ifndef HELPERS_H
#define HELPERS_H

struct Node {
  double x, y;
  Node(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

struct Edge {
  int src, dest;
  double weight;

  Edge(int s = 0, int d = 0, double w = 0) : src(s), dest(d), weight(w) {}

  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

#endif //HELPERS_H
