#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iosfwd>
#include <vector>

namespace taskaevv
{
  struct Point
  {
    int x_, y_;
  };

  struct Polygon
  {
    std::vector < taskaev::Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}
#endif
