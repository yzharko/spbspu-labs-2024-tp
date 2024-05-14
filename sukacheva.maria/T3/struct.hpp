#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iosfwd>
#include <vector>

namespace sukacheva
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& applicant);
  std::istream& operator>>(std::istream& in, Polygon& applicant);
  std::ostream& operator<<(std::ostream& out, Point& point);
  bool operator==(const Point& left, const Point& right);
}

#endif
