#include "struct.hpp"
#include <iostream>
#include "Delimeter.hpp"
#include "StreamGuard.hpp"

std::istream& sukacheva::operator>>(std::istream& in, Point& applicant)
{
  std::istream::sentry guard(in);
  Point point;
  if (!guard)
  {
    return in;
  }
  in >> Delimeter{ '(' } >> point.x >> Delimeter{ ';' } >> point.y >> Delimeter{ ')' };
  if (in)
  {
    applicant = point;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& sukacheva::operator>>(std::istream& in, Polygon& applicant)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Polygon polygon;
  Point point;
  size_t vertices = 0;
  in >> vertices;
  if (!in || vertices < 3)
  {
    in.setstate(std::ios::failbit);
  }
  for (size_t i = 0; i < vertices; i++)
  {
    if (in >> point)
    {
      polygon.points.push_back(point);
    }
  }
  if (vertices == polygon.points.size())
  {
    applicant = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool sukacheva::operator==(const Point& left, const Point& right)
{
  return (left.x == right.x) && (left.y == right.y);
}

bool sukacheva::operator!=(const Point& left, const Point& right)
{
  return (left.x != right.x) || (left.y != right.y);
}
