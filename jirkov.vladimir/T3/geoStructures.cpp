#include "geoStructures.hpp"
#include <iostream>
#include "DelimiterIO.hpp"
#include "IOstructures.hpp"

std::istream& jirkov::operator>>(std::istream& in, Point& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point point;
  in >> Del{'('} >> value.x >> Del{';'} >> value.y >> Del{')'};
  if (in)
  {
    value = point;
  }
  return in;
}

std::istream& jirkov::operator>>(std::istream& in, Polygon& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Polygon polygon;
  size_t size;
  if (!(in >> size))
  {
    in.setstate(std::ios::failbit);
  }
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
  }
  Point point;
  for (size_t i = 0; i < size; i++)
  {
    if (in >> point)
    {
      polygon.points.push_back(point);
    }
  }
  if (in && size == polygon.points.size())
  {
    value = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
