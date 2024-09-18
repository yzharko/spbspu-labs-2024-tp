#ifndef POLYGON_FUNCTIONS_HPP
#define POLYGON_FUNCTIONS_HPP

#include "polygon.hpp"

namespace ponomarev
{
  double getArea(const Polygon & polygon);
  int getValue(const Point & first, const Point & second);

  double sumEven(double res, const Polygon & polygon);
  double sumOdd(double res, const Polygon & polygon);
  double sumAll(double res, const Polygon & polygon);
  double sumIfNumOfVertexes(double res, const Polygon & polygon, size_t numOfVertexes);

  int getNumOfVertexes(const Polygon & polygon);

  bool isEven(const Polygon polygon);
  bool isOdd(const Polygon polygon);
  bool isEqually(const Polygon polygon, size_t numOfVertexes);
  bool isRect(const Polygon polygon);
  bool isOrthogonal(const Point a, const Point b, const Point c);
  bool isIntersection(const Polygon & first, const Polygon & second);
  bool whichBiggerX(const Point & first, const Point & second);
  bool whichBiggerY(const Point & first, const Point & second);
  bool whichSmallerX(const Point & first, const Point & second);
  bool whichSmallerY(const Point & first, const Point & second);
}

#endif
