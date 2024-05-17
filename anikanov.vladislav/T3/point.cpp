#include "point.hpp"

#include <cmath>
#include <iostream>
#include <limits>

anikanov::Point &anikanov::Point::operator=(const anikanov::Point &point)
{
  x = point.x;
  y = point.y;
  return *this;
}

double anikanov::Point::operator-(const anikanov::Point &point) const
{
  return sqrt(pow(x - point.x, 2) + pow(y - point.y, 2));
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::Point &dest)
{
  char delimiter;
  in >> delimiter >> dest.x >> delimiter >> dest.y >> delimiter;
  return in;
}
