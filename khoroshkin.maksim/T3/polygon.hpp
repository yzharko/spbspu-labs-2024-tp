#define POLYGON_HPP
#ifdef POLYGON_HPP

#include <vector>
#include <iostream>
#include "datastruct.hpp"

namespace khoroshkin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & is, Point & dest);
  std::istream & operator>>(std::istream & is, Polygon & dest);
}

#endif
