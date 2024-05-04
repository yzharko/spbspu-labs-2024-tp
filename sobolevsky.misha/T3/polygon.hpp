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

  double getArea(const sobolevsky::Polygon& polygon);
  std::istream& operator>>(std::istream& in, sobolevsky::Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, sobolevsky::Polygon& polygon);
}

#endif
