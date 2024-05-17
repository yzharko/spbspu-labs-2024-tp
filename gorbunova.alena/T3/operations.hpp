#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include <vector>
#include <iosfwd>
#include "commands.hpp"

namespace gorbunova
{
  void areaOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  void areaEven(const std::vector< Polygon > &polygons, std::ostream &out);
  void areaMean(const std::vector< Polygon > &polygons, std::ostream &out);
  void areaNumOfVertexes(size_t vertexes, const std::vector< Polygon > &polygons, std::ostream &out);
  void maxArea(const std::vector< Polygon > &polygons, std::ostream &out);
  void maxVertexes(const std::vector< Polygon > &polygons, std::ostream &out);
  void minArea(const std::vector< Polygon > &polygons, std::ostream &out);
  void minVertexes(const std::vector< Polygon > &polygons, std::ostream &out);
  void countEven(const std::vector< Polygon > &polygons, std::ostream &out);
  void countOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  void countNumOfVertexes(size_t vertexes, const std::vector< Polygon > &polygons, std::ostream &out);
  double sumAreas(const std::vector< Polygon > &polygons);
  double getArea(const Polygon &polygon);
  bool checkPerms(const Polygon &lhs, const Polygon &rhs);
  bool isPointInShape(const Polygon &toCompare, const Point &point);
  void updateFrame(const Point &point, Point &topLeft, Point &bottomRight);
  bool pointInFrame(const Point &point, const Point &topLeft, const Point &bottomRight);
}

#endif
