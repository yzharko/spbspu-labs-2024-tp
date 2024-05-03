#ifndef CHECK_FUNCS_HPP
#define CHECK_FUNCS_HPP
#include <iostream>
#include "polygon.hpp"

namespace psarev
{
  double getArea(Polygon& poly);
  int getInterValue(Point& ptOne, Point& ptTwo);
  double plusArea(Polygon& poly, double summed);
  double sumAreasIfEven(double res, const Polygon& shape);
  double sumAreasIfOdd(double res, const Polygon& shape);
  double sumAreasIfEqual(double res, const Polygon& shape, size_t numOfVertexes);
  int getNumOfVertexes(const Polygon& shape);
  bool isNumOfVertexesEven(const Polygon shape);
  bool isNumOfVertexesOdd(const Polygon shape);
  bool isNumOfVertexesEqual(const Polygon shape, size_t numOfVertexes);
}

#endif