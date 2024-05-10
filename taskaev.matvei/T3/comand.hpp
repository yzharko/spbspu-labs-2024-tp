#ifndef COMAND_HPP
#define COMAND_HPP

#include <vector>
#include "polygon.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  double getAreas(const Point& pointOne, const Point& pointTwo);
  double getArea(const Polygon& polygon);

  void AreaEven(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaEven(double area, const Polygon& polygon);

  void AreaOdd(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaOdd(double area, const Polygon& polygon);

  void AreaMean(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaSum(double area, const Polygon& polygon);

  void AreaNum(const std::vector< Polygon >& polygon, std::ostream& out, size_t type);
  double getAreaNum(double area, const Polygon& polygon, size_t vertexes);

  
}
#endif
