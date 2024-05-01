#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
// #include <algorithm>
// #include <functional>
#include "figures.hpp"

namespace mihalchenko
{
  size_t getSize(const Polygon &polygon);
  double sumArea(double area, const Point &startPoint);
  double countArea(const Polygon &polygon);
  void printAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out);
  void printAreaEven(const std::vector<Polygon> &polygons, std::ostream &out);
}

#endif
