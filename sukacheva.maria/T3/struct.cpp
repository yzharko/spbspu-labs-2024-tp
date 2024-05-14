#include "struct.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
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
  size_t vertices = 0;
  in >> vertices;
  if (!in || vertices < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > tempPoints;
  tempPoints.reserve(vertices);
  std::copy
  (
    std::istream_iterator< Point >(in),
    std::istream_iterator< Point >(),
    std::back_inserter(tempPoints)
  );

  if (tempPoints.size() != vertices)
  {
    in.setstate(std::ios::failbit);
  }
  if (in)
  {
    std::copy
    (
      tempPoints.begin(),
      tempPoints.end(),
      std::back_inserter(polygon.points)
    );
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
