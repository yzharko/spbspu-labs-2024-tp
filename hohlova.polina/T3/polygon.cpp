#include <iostream>
#include "polygon.hpp"
#include "delimiter.hpp"

std::istream& hohlova::operator>>(std::istream& in, Point& dest)
{

  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point point{};
  using exp = DelimiterIO;
  if (in >> exp{ '(' } >> point.x >> exp{ ';' } >> point.y >> exp{ ')' })
  {
    dest = point;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& hohlova::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  };
  size_t numVertices = 0;
  in >> numVertices;
  if (numVertices < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > polygons;
  for (size_t i = 0; i < numVertices; i++)
  {
    Point currentPoint{};
    in >> currentPoint;
    polygons.push_back(currentPoint);
  }
  dest = Polygon{ polygons };
  return in;
}
bool hohlova::operator==(const Polygon& firstpolygon, const Polygon& secondpolygon)
{
  if (firstpolygon.points.size() != secondpolygon.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < firstpolygon.points.size(); ++i)
  {
    if (firstpolygon.points[i].x != secondpolygon.points[i].x || firstpolygon.points[i].y != secondpolygon.points[i].y)
    {
      return false;
    }
  }
  return true;
}
