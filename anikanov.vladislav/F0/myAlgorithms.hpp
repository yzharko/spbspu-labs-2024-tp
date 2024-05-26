#ifndef MYALGORITHMS_HPP
#define MYALGORITHMS_HPP

#include <vector>
#include <memory>
#include "sceneManager.hpp"

namespace anikanov {
  using matrix_t = std::vector< std::vector< int > >;
  bool checkMatrix(const std::vector< std::vector< int > > &matrix);
  std::vector< std::vector< int > > getEdges(const std::vector< std::vector< int > > &graph);
  int findNumberOfVertices(const std::vector< std::vector< int > > &edges);
  std::vector< std::vector< int > > toMatrix(const std::vector< std::vector< int > > &edges);
  void printAns(const matrix_t &edges, const int sum, const std::shared_ptr<SceneManager> &manager);

  int findParent(std::vector< int > &parent, int i);
  std::vector< std::vector< int > > runKruskalMST(std::vector< std::vector< int > > &edges, int V);
  void merge(std::vector< int > &parent, std::vector< int > &rank, int x, int y);
}

#endif
