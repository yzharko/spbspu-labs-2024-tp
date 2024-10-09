#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

namespace smolyakov
{
  struct Polygon
  {
    std::vector<Point> points;
  };
}

#endif
