#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <ios>

namespace miheev
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& rhs);
  std::ostream& operator>>(std::ostream& out, Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator>>(std::ostream& out, Polygon& rhs);

  double getArea(const Polygon&);
}

#endif