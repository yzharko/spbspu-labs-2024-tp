#include <istream>
#include <DelimiterIO.hpp>
#include "Polygon.hpp"

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points;
}

std::istream& operator>>(std::istream& is, Polygon& polygon)
{
  polygon.points.clear();
  int vertex_count;
  if (!(is >> vertex_count) || vertex_count < 3)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  for (int i = 0; i < vertex_count; ++i)
  {
    Point point;
    if (!(is >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' }))
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    polygon.points.push_back(point);
  }

  if (polygon.points.size() != static_cast<std::vector< Point >::size_type>(vertex_count))
  {
    is.setstate(std::ios::failbit);
  }

  return is;
}
