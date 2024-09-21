#include "polygon.hpp"
#include <iostream>
#include "delimeter.hpp"

std::istream& popov::operator>>(std::istream& in, Polygon& shape)
{
  Polygon polygon;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t count = 0;
  if (!(in >> count) or (count < 3))
  {
    in.setstate(std::ios::failbit);
  }
  Point points;
  using del = popov::DelimiterIO;
  for (size_t i = 0; i < count; i++)
  {
    in >> del{ '(' } >> points.x >> del{ ';' } >> points.y >> del{ ')' };
    if (in)
    {
      polygon.points.push_back(points);
    }
  }
  if ((count == polygon.points.size()) and (in))
  {
    shape = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
