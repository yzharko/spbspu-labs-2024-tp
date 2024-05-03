#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "polygon.hpp"

namespace khoroshkin
{
  void cmdArea(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processEven(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processOdd(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processMean(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  double sumAllAreas(const std::vector< Polygon > & polygons);
  void processAreaNum(size_t vertexes, const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  double getArea(const Polygon & polygon);

  void cmdMax(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processMaxArea(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processMaxVertexes(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);

  void cmdMin(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processMinArea(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processMinVertexes(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);

  void cmdCount(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processCountEven(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processCountOdd(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  void processCountVertexes(size_t vertexes, const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);

  void cmdPerms(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  bool checkPerms(const Polygon & lhs, const Polygon & rhs);
  bool checkPoints(const Polygon & toCompare, const Point & point);

  void cmdRightshapes(const std::vector< Polygon > & polygons, std::istream & is, std::ostream & out);
  bool isAngleRight(const Polygon & polygon);
}

#endif
