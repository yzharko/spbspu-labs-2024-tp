#include "polygon.hpp"
#include "delimiter.hpp"
#include <istream>

std::istream & ponomarev::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int x = 0;
  int y = 0;
  in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };
  dest.x = x;
  dest.y = y;
  return in;
}

std::istream & ponomarev::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t numPoints = 0;
  if (!(in >> numPoints) || numPoints <= 2)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > polygon;
  Point point;

  for (size_t i = 0; i < numPoints; i++)
  {
    if (in.get() == '\n')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (in >> point)
    {
      polygon.push_back(point);
    }
  }

  if (in && polygon.size() == numPoints && in.get() == '\n')
  {
    dest = Polygon{ polygon };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
