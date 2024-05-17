#include "polygon.hpp"
#include <iostream>

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
  dest.points.clear();
  size_t size;
  in >> size;
  for (size_t i = 0; i < size; ++i) {
    Point point;
    in >> point;
    dest.points.push_back(point);
  }
  return in;
}

