#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>
#include "point.hpp"

namespace anikanov {
  struct Polygon {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &in, Polygon &dest);
}

#endif
