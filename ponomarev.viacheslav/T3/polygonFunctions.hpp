#ifndef POLYGON_FUNCTIONS_HPP
#define POLYGON_FUNCTIONS_HPP

#include "polygon.hpp"

namespace ponomarev
{
  double getArea(const Polygon & polygon);
  int getValue(const Point & first, const Point & second);
  double sumEven(double res, const Polygon & polygon);
  double sumIfNumOfVertexes(double res, const Polygon & polygon, size_t numOfVertexes);
}

#endif
