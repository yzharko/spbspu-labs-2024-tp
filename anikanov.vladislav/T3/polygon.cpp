#include "polygon.hpp"
#include <cmath>
#include <numeric>
#include <iostream>
#include <limits>
#include <inDelim.hpp>

#include "mainExtensions.hpp"

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

  if (!readPoints(in, dest.points, size)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (dest.points.size() != size) {
    in.setstate(std::ios::failbit);
  }

  return in;
}
