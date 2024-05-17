#define DATASTRUCT_HPP
#ifdef DATASTRUCT_HPP

#include <vector>
#include <iostream>
#include "delimiter.hpp"

namespace gorbunova
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector<Point> points;
  };

  std::istream &operator>>(std::istream &is, Point &dest);
  std::istream &operator>>(std::istream &is, Polygon &dest);
}

#endif
