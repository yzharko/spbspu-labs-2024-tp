#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <fstream>
#include <vector>
#include "point.hpp"

namespace sobolevsky
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, sobolevsky::Polygon& polygon);
}

#endif
