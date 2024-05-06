#ifndef INTERNAL_FUNCS_HPP
#define INTERNAL_FUNCS_HPP
#include "polygon.hpp"

namespace psarev
{
  double getArea(Polygon& poly);
  int getInterValue(Point& ptOne, Point& ptTwo);
  size_t getNumVerts(Polygon& poly);

  size_t getOddVerts(size_t summed, Polygon& poly);
  size_t getEvenVerts(size_t summed, Polygon& poly);
  size_t getSpecVerts(size_t summed, Polygon& poly, size_t& numVerts);

  bool isRect(Polygon& poly);

  double plusArea(double summed, Polygon& poly);
  double plusEvenArea(double summed, Polygon& poly);
  double plusOddArea(double summed, Polygon& poly);
  double plusSameArea(double summed, Polygon& poly, size_t& numVerts);

  size_t getRects(size_t summed, Polygon& poly);

  Polygon makeFrame(std::vector< Polygon >& polyVec);
  int getMaxX(Polygon& poly);
  int getMinX(Polygon& poly);
  int getX(Point& pt);

  int getMaxY(Polygon& poly);
  int getMinY(Polygon& poly);
  int getY(Point& pt);
}

#endif
