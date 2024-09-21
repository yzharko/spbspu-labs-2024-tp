#ifndef EDGE_HPP
#define EDGE_HPP
#include <utility>
#include <iostream>

struct Edge : public std::pair<int, int> {
  int weight;

  Edge();
  Edge(int v1, int v2, int w);

  bool operator==(const Edge& other) const;
  bool operator<(const Edge& other) const;
};

std::ostream& operator<<(std::ostream& out, const Edge& edge);

#endif
