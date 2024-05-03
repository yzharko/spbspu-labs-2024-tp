#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>
#include <algorithm>
#include <fstream>
#include "dataStruct.hpp"

namespace nikiforov
{
  std::string cutOption(std::string cmd);

  void takingArea(const std::vector< Polygon >& figure, std::istream&, std::ostream& out);
  double getPoints(const Point& first, const Point& second);
  double getArea(const Polygon& polygon);

  bool isOdd(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool numOfVert(int num, const Polygon& polygon);

  void takingMax(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out);
  size_t numOfVertexes(const Polygon& polygon);

  void takingMin(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out);
}

#endif
