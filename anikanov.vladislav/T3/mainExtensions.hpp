#ifndef MAINEXTENSIONS_HPP
#define MAINEXTENSIONS_HPP

#include <functional>
#include <string>
#include "vector"
#include "polygon.hpp"

namespace anikanov {
  void printErrorMessage(std::ostream& out);
  double getLenght(const Point &p1, const Point &p2);
  double getArea(const Polygon &polygon);
  double areaHelper(const Point &point1, const Point &point2);
  std::vector< Polygon > readPolygons(const std::string &filename);
  std::vector< double > getAreas(const std::vector< Polygon > &polygons);
  std::vector< double > getAreasIf(const std::vector< Polygon > &polygons, std::function< bool(const Polygon &) >);
  std::vector< size_t > getVertexes(const std::vector< Polygon > &polygons);
  void area(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void min(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void max(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void rects(const std::vector< Polygon > &polygons, std::istream &, std::ostream &out);
  void rightShapes(const std::vector< Polygon > &polygons, std::istream &, std::ostream &out);
  bool isRightAngle(const anikanov::Point &A, const anikanov::Point &B, const anikanov::Point &C);
  bool hasRightAngle(const anikanov::Polygon &polygon, size_t index = 0);
}

#endif
