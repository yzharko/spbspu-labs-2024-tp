#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace doroshenko
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& is, Point& dest);
  std::istream& operator>>(std::istream& is, Polygon& dest);
}

#endif
