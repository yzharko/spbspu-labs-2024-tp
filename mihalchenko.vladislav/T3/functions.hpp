#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// #include <vector>
#include <algorithm>
#include <functional>
#include "figures.hpp"

namespace mihalchenko
{
  size_t getSize(const Polygon &polygon);
  double getPoints(const Point &first, const Point &second);
  double sumArea(double area, const Point &startPoint);
  double countArea(const Polygon &polygon);
  void getAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out);
  void getAreaEven(const std::vector<Polygon> &polygons, std::ostream &out);
  void getAreaMean(const std::vector<Polygon> &polygons, std::ostream &out);
  void getAreaVertexes(const std::vector<Polygon> &polygons, size_t num, std::ostream &out);
  std::ostream &getAreaResult(const std::vector<Polygon> &polygons, bool predicate, std::ostream &out);
  void printArea(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out);
}

#endif
