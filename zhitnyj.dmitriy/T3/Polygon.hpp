#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <vector>
#include "Point.hpp"

struct Polygon
{
  std::vector< Point > points;

  friend std::istream& operator>>(std::istream& is, Polygon& polygon);
};

bool operator==(const Polygon& lhs, const Polygon& rhs);

#endif
