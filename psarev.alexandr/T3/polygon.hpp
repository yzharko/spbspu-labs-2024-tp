#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <ios>

namespace psarev
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& figure);
}

#endif
