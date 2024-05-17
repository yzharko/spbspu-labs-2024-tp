#include "polygon.hpp"
#include <iostream>
#include <limits>

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
  if (in.fail()) {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  for (size_t i = 0; i < size; ++i) {
    Point p;
    in >> p;
    if (in.fail()) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    dest.points.push_back(p);
  }

  return in;
}
