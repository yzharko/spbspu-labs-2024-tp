#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>

#include <vector>
#include <set>

#include "Edge.hpp"

class Graph {
public:
  Graph() = default;
  bool isEmpty() const;
  bool containVertex(int v) const;
  void insertVertex(int v);
  void removeVertex(int v);

  bool containEdge(const Edge& edge) const;
  bool insertEdge(const Edge& edge);
  void removeEdge(const Edge& edge);

  int weightEdges() const;

  bool load(const std::string& fileName);

  Graph kruskal() const;

  Graph prima() const;

  friend std::ostream& operator<<(std::ostream& out, const Graph& graph);

private:
  std::vector<Edge> edges_;
  std::set<int> vertices_;
};

#endif
