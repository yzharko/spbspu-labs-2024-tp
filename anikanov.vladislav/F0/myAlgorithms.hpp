#ifndef MYALGORITHMS_HPP
#define MYALGORITHMS_HPP

#include <vector>

namespace anikanov {
  bool checkMatrix(const std::vector< std::vector< int > > &matrix);
  std::vector< std::vector< int > > getEdges(const std::vector< std::vector< int > > &graph);
  int findParent(std::vector< int > &parent, int i);
  std::vector< std::vector< int > > runKruskalMST(std::vector< std::vector< int > > &edges, int V);
  void merge(std::vector< int > &parent, std::vector< int > &rank, int x, int y);
}

#endif
