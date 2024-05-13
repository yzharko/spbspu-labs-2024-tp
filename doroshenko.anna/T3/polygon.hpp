#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace doroshenko
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& is, Point& dest);
  std::istream& operator>>(std::istream& is, Polygon& dest);
  bool operator==(const Point& other) const;
  bool operator==(const Polygon& other) const;
}

#endif
