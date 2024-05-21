#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <vector>
#include <algorithm>
#include "separators.hpp"
#include "dataTypes.hpp"
namespace zheleznyakov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Point & ref);
  std::ostream & operator<<(std::ostream & out, const Point & ref);
  bool operator==(const Point & point1, const Point & point2);

  std::istream & operator>>(std::istream & in, Polygon & ref);
  std::istream & readPoint(std::istream & in, Polygon & ref, std::vector< Point > & polygon, size_t pointsAmount, size_t i);
  std::ostream & operator<<(std::ostream & out, const Polygon & ref);
  bool operator==(const Polygon & poly1, const Polygon & poly2);

  double calculateCrossProduct(const Point & p1, const Point & p2);
  double calculatePolygonArea(const Polygon & poly, int i, double area);
}
#endif
