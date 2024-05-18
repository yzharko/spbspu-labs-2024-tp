#include "polygon.hpp"
#include <iostream>
#include <limits>
#include <inOutPut.hpp>

anikanov::Polygon &anikanov::Polygon::operator=(const anikanov::Polygon &polygon)
{
  points = polygon.points;
  return *this;
}

size_t anikanov::Polygon::operator%(const size_t number) const
{
  return points.size() % number;
}

anikanov::Point &anikanov::Polygon::operator[](size_t index)
{
  return points[index];
}

size_t anikanov::Polygon::getSize() const
{
  return points.size();
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  dest.points.clear();

  size_t size;

  if (!(in >> size) || size < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  for (size_t i = 0; i < size; ++i) {
    Point p;

    if (!(in >> p)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    dest.points.push_back(p);
  }

  if (dest.getSize() != size)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
double anikanov::Polygon::getArea() const
{
  return 1;
}
