#ifndef POINT_HPP
#define POINT_HPP
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "guard.hpp"

namespace sadofeva
{
  struct Point
  {
    int x, y;
    bool operator == (const Point& other) const
    {
      return x == other.x && y == other.y;
    }
  };
  struct Polygon
  {
    std::vector< Point > point;
  };
  std::istream& operator>>(std::istream& is, Point& value);
  std::ostream& operator<<(std::ostream& out, const Point& value);
  std::istream& operator>>(std::istream& is, Polygon& value);
  std::ostream& operator<<(std::ostream& out, const Polygon& value);
}
#endif

