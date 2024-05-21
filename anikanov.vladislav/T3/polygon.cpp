#include "polygon.hpp"
#include <cmath>
#include <numeric>
#include <iostream>
#include <limits>
#include <inDelim.hpp>

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
    int x, y;

    if (!(in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' })) {
      in.setstate(std::ios::failbit);
      return in;
    }

    Point p{x, y};

    dest.points.push_back(p);
  }

  if (dest.points.size() != size) {
    in.setstate(std::ios::failbit);
  }

  return in;
}
