#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>
#include "InpOutTypes.hpp"

namespace zasulsky
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& in, Point& data);
  std::ostream& operator<<(std::ostream& out, const Point& data);
  bool operator==(const Point& lhs, const Point& rhs);
  bool lessX(Point lhs, Point rhs);
  bool lessY(Point lhs, Point rhs);


  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  double countArea(const Polygon& pol);
  void skipUntilNewLine(std::istream& in);
  std::pair< Point, Point > getFrame(const Polygon& pol);
  size_t getSize(const Polygon& polygon);
  using frame = std::pair< Point, Point >;
  frame getOverallFrame(const std::vector< Polygon >& polygons);
  bool isRightAngle(int v1x, int v2x, int v1y, int v2y);
  bool checkForRect(const Polygon& pol);
  bool IsEqual(Polygon lhs, Polygon rhs);
  double sumPmArea(double acc, const Point& p1);
}

#endif
