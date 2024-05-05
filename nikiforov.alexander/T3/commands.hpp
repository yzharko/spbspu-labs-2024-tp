#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>
#include <algorithm>
#include "dataStruct.hpp"

namespace nikiforov
{
  void takingArea(const std::vector< Polygon >& shapes, std::istream&, std::ostream& out);
  int getPoints(const Point& first, const Point& second);
  double getArea(const Polygon& polygon);

  bool isOdd(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool numOfVert(size_t num, const Polygon& polygon);

  void takingMax(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  size_t countOfVertexes(const Polygon& polygon);

  void takingMin(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);

  void takingCount(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);

  double getAreaResult(const std::vector< Polygon >& shapes, std::string mode);
  size_t getVertexesResult(const std::vector< Polygon >& shapes, std::string mode);
}

#endif
