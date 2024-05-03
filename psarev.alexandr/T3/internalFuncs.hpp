#ifndef INTERNAL_FUNCS_HPP
#define INTERNAL_FUNCS_HPP
#include <iostream>
#include "polygon.hpp"

namespace psarev
{
  double getArea(Polygon& poly);
  int getInterValue(Point& ptOne, Point& ptTwo);
  double plusArea(Polygon& poly, double summed);

  double plusEvenArea(Polygon& poly, double summed);
  double plusOddArea(Polygon& poly, double summed);

  //double sumAreasIfOdd(double res, const Polygon& shape);
  //double sumAreasIfEqual(double res, const Polygon& shape, size_t numOfVertexes);
  //int getNumOfVertexes(const Polygon& shape);
  //bool isNumOfVertexesEven(const Polygon shape);
  //bool isNumOfVertexesOdd(const Polygon shape);
  //bool isNumOfVertexesEqual(const Polygon shape, size_t numOfVertexes);
}

#endif