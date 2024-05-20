#include "point.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <inOutPut.hpp>

anikanov::Point &anikanov::Point::operator=(const anikanov::Point &point)
{
  x = point.x;
  y = point.y;
  return *this;
}

int anikanov::Point::operator-(const anikanov::Point &other) const
{
  return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::Point &dest)
{
  using namespace anikanov;
  in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
  return in;
}
