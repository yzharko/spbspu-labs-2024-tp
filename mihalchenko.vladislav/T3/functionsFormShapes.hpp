#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <algorithm>
#include <functional>
#include "figures.hpp"

namespace mihalchenko
{
  size_t getSize(const Polygon &polygon);
  double getPoints(const Point &first, const Point &second);

  double sumArea(double area, const Point &startPoint);
  double countArea(const Polygon &polygon);

  void getAreaOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  void getAreaEven(const std::vector< Polygon > &polygons, std::ostream &out);
  void getAreaMean(const std::vector< Polygon > &polygons, std::ostream &out);
  void getAreaVertexes(const std::vector< Polygon > &polygons, size_t num, std::ostream &out);
  std::ostream &getAreaResult(const std::vector< Polygon > &polygons, bool predicate, std::ostream &out);

  int getNumOfVertexes(const Polygon &polygons);

  std::ostream &getMaxArea(const std::vector< Polygon > &polygons, std::ostream &out);
  std::ostream &getMaxVertexes(const std::vector< Polygon > &polygons, std::ostream &out);
  std::ostream &getMinArea(const std::vector< Polygon > &polygons, std::ostream &out);
  std::ostream &getMinVertexes(const std::vector< Polygon > &polygons, std::ostream &out);

  std::ostream &countEven(const std::vector< Polygon > &polygons, std::ostream &out);
  std::ostream &countOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  std::ostream &countVertexes(const std::vector< Polygon > &polygons, size_t num, std::ostream &out);

  long long getLength(const Polygon &polygon);
  bool isLengthCorrect(const Polygon &lhsPolygon, const Polygon &rhsPolygon);
  bool isPointCorrect(const Point &lhsPoint, const Point &rhsPoint);
  bool arePointsCorrect(const Polygon &polygon, const Point &point);

  Point getVector(const Point &lhs, const Point &rhs);
  double getCos(const Point &lhs, const Point &rhs);
  bool isZeroCos(const double &cos);
  bool isRightPolygon(const Polygon &polygon);
}

#endif
