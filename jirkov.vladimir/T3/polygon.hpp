#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"
#include <vector>

namespace jirkov
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& value);
  std::ostream& operator<<(std::ostream& out, const Polygon& value);
}

#endif

