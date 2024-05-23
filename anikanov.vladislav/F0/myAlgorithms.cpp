#include "myAlgorithms.hpp"

#include <vector>

bool anikanov::checkMatrix(const std::vector< std::vector< int > > &matrix)
{
  int n = matrix.size();

  for (int i = 0; i < n; ++i) {
    if (matrix[i][i] != 0) {
      return false;
    }
    for (int j = 0; j < i; ++j) {
      if (matrix[i][j] != matrix[j][i]) {
        return false;
      }
    }
  }

  return true;
}
