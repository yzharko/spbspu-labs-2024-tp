#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <ios>
#include <vector>

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
  //std::ostream& operator<<(std::ostream& out, const Polygon& figure);
  //bool operator<(const Polygon& fFigure, const Polygon& sFigure);
}

#endif