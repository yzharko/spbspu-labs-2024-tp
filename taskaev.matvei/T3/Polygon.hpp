#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iosfwd>
#include <vector>

namespace taskaev
{
  struct Point
  {
    int x_, y_;
  };

  struct Polygon
  {
    std::vector < Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& first, const Polygon& second);
  bool operator==(const Point& first, const Point& second);
}
#endif
