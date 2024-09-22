#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <vector>
#include <iostream>

namespace popov
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& shape);
}

#endif
